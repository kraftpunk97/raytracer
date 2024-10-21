#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.hpp"
#include "interval.hpp"

namespace rt {
    class HitRecord {
    public:
        Point3 p;
        Vec3 normal;
        double t;
        bool front_face;

        void set_front_normal(const Ray& r, const Vec3& outward_normal);
    };

    class Hittable {
    public:
        virtual ~Hittable() = default;

        virtual bool hit(const Ray& ray, const Interval ray_t, HitRecord& record) const = 0;
    };
};

#endif