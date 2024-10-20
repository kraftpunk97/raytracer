#include <cmath>
#include "sphere.hpp"

namespace rt {
    Sphere::Sphere(const Point3& center, double radius) {
        this->center = center;
        this->radius = std::fmax(0, radius);
    }

    bool Sphere::hit(const Ray& ray, double ray_tmin, double ray_tmax, HitRecord& record) const {
        Vec3 oc = center - ray.origin();
        auto a = ray.direction().len_sq();
        auto h = dot(ray.direction(), oc);
        auto c = oc.len_sq() - radius*radius;
        auto discriminant = h*h - a*c;

        if (discriminant < 0) { return false; }

        auto sqrtd = std::sqrt(discriminant);

        // Find the nearest root that lies in the accepable range
        auto root = (h-sqrtd) / a;
        if (root<=ray_tmin || ray_tmax<=root) {
            root = (h+sqrtd) / a;
            if (root<=ray_tmin || ray_tmax<=root) { return false; }
        }

        record.t = root;
        record.p = ray.at(record.t);
        auto outward_normal = (record.p-center)/radius;
        record.set_front_face(ray, outward_normal);

        return true;
    }
};