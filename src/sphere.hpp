#ifndef SPEHRE_H
#define SPHERE_H

#include "hittable.hpp"
#include "point.hpp"


namespace rt {
    class Sphere: public Hittable {
    private:
        Point3 center;
        double radius;

    public:
        Sphere(const Point3& center, double radius);
        bool hit(const Ray& ray, double ray_tmin, double ray_tmax, HitRecord& record) const override;
    };
};

#endif