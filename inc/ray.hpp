#ifndef RAY_HPP
#define RAY_HPP

#include "vec3.hpp"

/**
 * @brief A ray can be represented by P(t) = A + tB,
 * where P is the point, A is the origin (point), B is the direction (vector) 
 * and t determines how far the vector goes 
 */

class Ray {
  public:
    Ray() {}

    Ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}

    point3 Origin() const  { return orig; }
    vec3 Direction() const { return dir; }

    point3 PointRayAt(double t) const {
        return orig + t*dir;
    }

  private:
    point3 orig;
    vec3 dir;
};

#endif 