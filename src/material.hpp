#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.hpp"
#include "hittable.hpp"

namespace rt {
    class Material {
    public:
        virtual ~Material() = default;
        
        /*
         * Direct the ray towards some direction based on the properties of the material
         * The new ray is represnted by `ray_scattered`, and its color is given by `attenuation`.
         */
        virtual bool scatter(const Ray& ray_in, const HitRecord& record,
                             Color& attenuation, Ray& ray_scattered) const {
            return false;
        };

    };

    class Lambertian: public Material {
    private:
        Color albedo;
    
    public:
        Lambertian(const Color& albedo);

        bool scatter(const Ray& ray_in, const HitRecord& record,
                     Color& attenuation, Ray& ray_scattered) const override;
    };

    class Metal: public Material {
    private:
        Color albedo;
        double fuzz_factor;

    public:
        Metal(const Color& albedo, double fuzz_factor);

        bool scatter(const Ray& ray_in, const HitRecord& record,
                     Color& attenuation, Ray& ray_scattered) const override;
    };
};

#endif