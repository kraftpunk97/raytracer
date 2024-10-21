#include "hittable.hpp"

namespace rt {
    void HitRecord::set_front_normal(const Ray& ray, const Vec3& outward_normal) {
        // Sets the hit record  normal vector.
        // NOTE: It is assumed that the `outward_normal` parameter is of unit length
        front_face = dot(ray.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
}