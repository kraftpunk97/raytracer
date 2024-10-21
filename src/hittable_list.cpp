#include "hittable_list.hpp"

namespace rt {
    HittableList::HittableList(){}
    HittableList::HittableList(std::shared_ptr<Hittable> object) { add(object); }

    void HittableList::add(std::shared_ptr<Hittable> object) { objects.push_back(object); }
    void HittableList::clear() { objects.clear(); }
    
    bool HittableList::hit(const Ray& ray, const Interval ray_t, HitRecord& record) const {
        HitRecord temp;
        bool hit_anything = false;
        auto closest_so_far = ray_t.max;

        for (const auto& object: objects) {
            if (object->hit(ray, Interval(ray_t.min, closest_so_far), temp)) {
                hit_anything = true;
                closest_so_far = temp.t;
                record = temp;
            }
        }

        return hit_anything;
    }
};