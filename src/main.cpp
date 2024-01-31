#include "rtweekend.hpp"

#include "color.hpp"
#include "hittable_object.hpp"
#include "hittable_list.hpp"
#include "sphere.hpp"

#include "../libs/SFML-2.5.1/include/SFML/Graphics/Image.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

//Returns light intensity
double Shader(const vec3& rec_point, const vec3& rec_normal, HittableObject& world, const Ray& shadow_ray, HitRecord& shadow_rec, int depth) {
    //intensity varies between 0 and 50 based on current light position
    double intensity = 0.0;
    
    //generates a random point within the light source and shoot the shadow ray towards there
    for (int i = 0; i < depth; ++i) {
        if (world.Hit(shadow_ray, 0.001, infinity, shadow_rec)) {
            vec3 random_point_on_light = global_light_position + random_point_on_light.Random();
            vec3 light_direction_from_shadow = (random_point_on_light - rec_point);
            double cos_theta = dot(rec_normal, light_direction_from_shadow);
            intensity += std::max(0.0, cos_theta);
        }
    }
    
    //adjust lighting intensity based on distance between hit pixel and light source 
    double attenuation = CalculateDistance(rec_point, global_light_position);
    return (std::max(intensity, 20.0) / depth) / (attenuation * depth);
}

color RayColor(const Ray& r, HittableObject& world) {
    HitRecord rec;
    if (world.Hit(r, 0, infinity, rec)) {
        Ray shadow_ray(rec.GetPoint(), global_light_direction);
        double val = CalculateDistance(rec.GetPoint(), ground_coordinates);

        //create additional shadow rays to check for the object's shadow on the ground
        if (world.Hit(shadow_ray, 0.001, infinity, rec) && val <= ground_radius + 0.001) {
            
            double light_intensity = Shader(rec.GetPoint(), rec.GetNormal(), world, r, rec, 10);
            return 1.5 * light_intensity * (color(1, 1, 1) + rec.GetNormal());
        }
        double light_intensity = Shader(rec.GetPoint(), rec.GetNormal(), world, r, rec, 10);
        return 4 * light_intensity * (color(1, 1, 1) + rec.GetNormal());
    }

    //if nothing is hit, create a blue background
    vec3 unit_direction = UnitVector(r.Direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (CalculateDistance(rec.GetPoint(), global_light_position)/100) * (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

int main() {

    // Image
    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 1028;
    
    // Calculate the image height, and ensure that it's at least 1.
    int image_height = static_cast<int>(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // Filepath to export image
    const std::string output_file = "image.png";

    // World
    HittableList world;
    
    world.add(make_shared<Sphere>(ground_coordinates, ground_radius)); //ground
    world.add(make_shared<Sphere>(point3(-0.1,-0.3,-1), 0.2));
    world.add(make_shared<Sphere>(point3(0.2,0.2,-1), 0.2));
    world.add(make_shared<Sphere>(point3(-2,0,-3), 1));

    // Camera
    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (static_cast<double>(image_width)/image_height);
    auto camera_center = point3(0, 0, 0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left = camera_center
                             - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // Create empty image
    sf::Image img;
    img.create(image_width, image_height, sf::Color::White);

    for (int j = 0; j < image_height; ++j) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            Ray r(camera_center, ray_direction);

            //check if it hit an object, if yes then assign the pixel a colour
            color col = RayColor(r, world);

            // Setting the color of each pixel
            img.setPixel(i, j, sf::Color(255*col[0], 255*col[1], 255*col[2]));
        }
    }

    if (img.saveToFile(output_file)) {
        std::clog << "\rImage file saved succesfully!" << std::endl;
        return 0;
    } else {
        std::clog << "\rImage file save failed" << std::endl;
        return -1;
    }

    std::clog << "\rDone.                 \n";
}