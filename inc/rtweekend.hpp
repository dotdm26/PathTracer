#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>

// Usings

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions
inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline double RandomDouble() {
    return rand() / (RAND_MAX + 1.0);
}

inline double RandomDouble(double min, double max) {
    return min + (max-min)*RandomDouble();
}

// Common Headers
#include "ray.hpp"
#include "vec3.hpp"

//Light source (top right area)
point3 global_light_position = vec3(2.5, 4, -1);
vec3 global_light_direction = global_light_position - vec3(0, 0, 0);

//Ground coordinates
point3 ground_coordinates = point3(0,-100.5,-1); //modify as you wish
double ground_radius = 100.0; //modify as you wish

double CalculateDistance(const point3& p1, const point3& p2) {
    vec3 v = p2 - p1;
    return std::sqrt(v.x()*v.x() + v.y()*v.y() + v.z()*v.z());
}

#endif