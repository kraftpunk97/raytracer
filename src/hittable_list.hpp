#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <vector>
#include <memory>
#include "hittable.hpp"

namespace rt {
    class HittableList: public Hittable {
    public:
        std::vector<std::shared_ptr<Hittable>> objects;

        HittableList();
        HittableList(std::shared_ptr<Hittable> object);

        void clear();
        void add(std::shared_ptr<Hittable> object);
        
        bool hit(const Ray& ray, double ray_tmin, double ray_tmax, HitRecord& record) const override;
    };
};
#endif