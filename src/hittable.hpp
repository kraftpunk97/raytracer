#ifndef HITTABLE_H
#define HITTABLE_H

#include "vec.hpp"
#include "point.hpp"
#include "ray.hpp"

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

        virtual bool hit(const Ray& ray, double ray_tmin, double t_max, HitRecord& record) const = 0;
    };
};
#endif