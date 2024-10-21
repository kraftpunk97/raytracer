#ifndef SPEHRE_H
#define SPHERE_H

#include "hittable.hpp"
#include "interval.hpp"


namespace rt {
    class Sphere: public Hittable {
    private:
        Point3 center;
        double radius;

    public:
        Sphere(const Point3& center, double radius);
        bool hit(const Ray& ray, const Interval ray_t, HitRecord& record) const override;
    };
};

#endif