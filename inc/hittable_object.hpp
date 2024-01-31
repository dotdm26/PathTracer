#ifndef HITTABLE_OBJECT_HPP
#define HITTABLE_OBJECT_HPP

#include "ray.hpp"

/**
 * @brief Records information about the area hit by the ray
 */
class HitRecord {
public:
  void SetFaceNormal(const Ray& r, const vec3& outward_normal) {
    front_face = dot(r.Direction(), outward_normal) < 0; // check if ray is outside the surface
    normal = front_face ? outward_normal : -outward_normal; //ensure that surface normal always points outwards when ray hits the surface
  }

  const point3& GetPoint() const {return p;}
  const vec3& GetNormal() const {return normal;}
  const double& GetT() const {return t;}

  void SetPoint(const point3& p) {this->p = p;}
  void SetT(const double& t) {this->t = t;}
private:
  point3 p;
  vec3 normal;
  double t;
  bool front_face;
};

/**
 * @brief HittableObject is an object that can be hit by a ray.
 */
class HittableObject {
  public:
    HittableObject() {}
    virtual ~HittableObject() = default;
    virtual bool Hit(const Ray& r, double ray_tmin, double ray_tmax, HitRecord& rec) const = 0;
};

#endif