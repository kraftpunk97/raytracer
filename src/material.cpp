#include "material.hpp"

namespace rt {
    Lambertian::Lambertian(const Color& albedo) {
        this->albedo = albedo;
    }

    bool Lambertian::scatter(const Ray& ray_in, const HitRecord& record,
                             Color& attenuation, Ray& ray_scattered) const {
        auto scatter_direction = record.normal + random_unit_vector();

        if (scatter_direction.near_zero()) { scatter_direction = record.normal; }
        
        ray_scattered = Ray(record.p, scatter_direction);
        attenuation = albedo;
        return true;
    }

    Metal::Metal(const Color& albedo, double fuzz_factor) {
        this->albedo = albedo;
        this->fuzz_factor = fuzz_factor>1 ? 1 : fuzz_factor;
    }

    bool Metal::scatter(const Ray& ray_in, const HitRecord& record,
                        Color& attenuation, Ray& ray_scattered) const {
        auto reflect_direction = reflect(ray_in.direction(), record.normal);
        reflect_direction = unit_vector(reflect_direction) + (fuzz_factor*random_unit_vector());
        ray_scattered = Ray(record.p, reflect_direction);
        attenuation = albedo;
        
        // If the fuzzy reflected ray is scattered below the surface, just absorb them.
        return (dot(reflect_direction,record.normal) > 0);
    }
};  