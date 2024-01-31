#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable_object.hpp"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class HittableList : public HittableObject {
  public:
    std::vector<shared_ptr<HittableObject>> objects;

    HittableList() {}
    HittableList(shared_ptr<HittableObject> object) { add(object); }

    void clear() { objects.clear(); }

    void add(shared_ptr<HittableObject> object) {
        objects.push_back(object);
    }

    bool Hit(const Ray& r, double ray_tmin, double ray_tmax, HitRecord& rec) const override {
        HitRecord temp_rec;
        bool hit_anything = false;
        auto closest_so_far = ray_tmax;

        for (const auto& object : objects) {
            if (object->Hit(r, ray_tmin, closest_so_far, temp_rec)) {
                hit_anything = true;
                closest_so_far = temp_rec.GetT();
                rec = temp_rec;
            }
        }

        return hit_anything;
    }

};

#endif
