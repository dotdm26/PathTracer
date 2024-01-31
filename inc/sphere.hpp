#ifndef SPHERE_H
#define SPHERE_H

#include "hittable_object.hpp"
#include "vec3.hpp"

/**
 * @brief A Sphere object derived from HittableObject class
 */
class Sphere : public HittableObject {
  public:
    Sphere(point3 _center, double _radius) : center(_center), radius(_radius) {}

    bool Hit(const Ray& r, double ray_tmin, double ray_tmax, HitRecord& rec) const override {
        //oc = point A - center C
        vec3 oc = r.Origin() - center;
        //abc are from the quadratic equation (-b +/- sqrt(b^2 - 4ac))/2a
        auto a = r.Direction().LengthSquared();
        auto half_b = dot(oc, r.Direction());
        auto c = oc.LengthSquared() - radius*radius;

        auto discriminant = half_b*half_b - a*c;
        if (discriminant < 0) return false; //< 0 = no intersection, 0 = 1 intersection, > 0 = 2 intersections 
        auto sqrtd = sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range. This checks for intersection points
        auto root = (-half_b - sqrtd) / a; //the entire quadratic formula
        if (root <= ray_tmin || ray_tmax <= root) {
            root = (-half_b + sqrtd) / a;
            if (root <= ray_tmin || ray_tmax <= root)
                return false;
        }

        rec.SetT(root);
        rec.SetPoint(r.PointRayAt(rec.GetT()));
        vec3 outward_normal = (rec.GetPoint() - center) / radius;
        rec.SetFaceNormal(r, outward_normal);

        return true;
    }
  private:
    point3 center;
    double radius;
};

#endif