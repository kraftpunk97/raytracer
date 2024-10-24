// Creating the first image.

#include "utils.hpp"
#include "hittable_list.hpp"
#include "sphere.hpp"
#include "camera.hpp"
#include "material.hpp"

int main(int argc, char* argv[]) {
    // Camera
    rt::Camera camera;
    camera.aspect_ratio = 16.0 / 9.0;
    camera.image_width = 400;
    camera.max_depth = 50;

    // Materials
    auto material_ground = std::make_shared<rt::Lambertian>(rt::Color(0.8,0.8,0.0));
    auto material_center = std::make_shared<rt::Lambertian>(rt::Color(0.1,0.2,0.5));
    auto material_left = std::make_shared<rt::Dielectric>(1.5);
    auto material_right = std::make_shared<rt::Metal>(rt::Color(0.8,0.6,0.2), 1);
    // World
    rt::HittableList world;
    world.add(std::make_shared<rt::Sphere>(rt::Point3(0,-100.5,-1), 100, material_ground));
    world.add(std::make_shared<rt::Sphere>(rt::Point3(0,0,-1.2), 0.5, material_center));
    world.add(std::make_shared<rt::Sphere>(rt::Point3(-1,0,-1), 0.5, material_left));
    world.add(std::make_shared<rt::Sphere>(rt::Point3(1,0,-1), 0.5, material_right));

    camera.render(world); // Render
    return 0;
}