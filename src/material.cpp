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

    Dielectric::Dielectric(double refraction_index) {
        this->refraction_index = refraction_index;
    }

    bool Dielectric::scatter(const Ray& ray_in, const HitRecord& record,
                             Color& attenuation, Ray& ray_scattered) const {
        double ri = record.front_face ? (1/refraction_index) : refraction_index;
        
        Vec3 ray_in_unit_vec = unit_vector(ray_in.direction());
        double cos_theta = dot(-ray_in_unit_vec, record.normal);
        double sin_theta = std::sqrt(1 - cos_theta*cos_theta);
        bool reflectance_satisfied = reflectance(cos_theta, ri) > random_double();  // Not really sure how this works...
        auto direction = (ri*sin_theta>1.0 || reflectance_satisfied) ? 
                            reflect(ray_in_unit_vec, record.normal) : 
                            refract(ray_in_unit_vec, record.normal, ri);
        ray_scattered = Ray(record.p, direction);
        attenuation = Color(1.0, 1.0, 1.0);
        return true;
    }

    double Dielectric::reflectance(double cos_theta, double refraction_index) {
            auto r0 = (1-refraction_index) / (1+refraction_index);  // Schlick's approx
            r0 = r0*r0;
            return r0 + (1-r0)*std::pow((1-cos_theta), 5);
    }
};  