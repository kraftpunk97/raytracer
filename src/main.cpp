// Creating the first image.

#include "utils.hpp"
#include "hittable_list.hpp"
#include "sphere.hpp"
#include "camera.hpp"
#include "material.hpp"


void populate_world(rt::HittableList& world) {
    // Ground
    auto ground_material = std::make_shared<rt::Lambertian>(rt::Color(0.5,0.5,0.5));
    world.add(std::make_shared<rt::Sphere>(rt::Point3(0,-1000,0), 1000, ground_material));

    // Random balls

    for (int a=-11; a<11; a++) {
        for (int b=-11; b<11; b++) {
            auto choose_mat = rt::random_double();
            rt::Point3 center(a + 0.9*rt::random_double(),
                              0.2,
                              b + 0.9*rt::random_double());
            
            if ((center - rt::Point3(4,0.2,0)).length() > 0.9) {
                std::shared_ptr<rt::Material> sphere_material;
                
                if (choose_mat < 0.8) { 
                    // Diffuse
                    auto albedo = rt::Color::random() * rt::Color::random();
                    sphere_material = std::make_shared<rt::Lambertian>(albedo);
                    world.add(std::make_shared<rt::Sphere>(center, 0.2, sphere_material));
                
                } else if (choose_mat < 0.95) { 
                    // Metal
                    auto albedo  = rt::Color::random(0.5, 1);
                    auto fuzz_factor = rt::random_double(0, 0.5);
                    sphere_material = std::make_shared<rt::Metal>(albedo, fuzz_factor);
                    world.add(std::make_shared<rt::Sphere>(center, 0.2, sphere_material));
                
                } else { 
                    // Glass
                    sphere_material = std::make_shared<rt::Dielectric>(1.5);
                    world.add(std::make_shared<rt::Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    // The Big 3

    auto material1 = std::make_shared<rt::Dielectric>(1.5);
    world.add(std::make_shared<rt::Sphere>(rt::Point3(0,1,0), 1.0, material1));

    auto material2 = std::make_shared<rt::Lambertian>(rt::Color(0.4, 0.2, 0.1));
    world.add(std::make_shared<rt::Sphere>(rt::Point3(-4,1,0), 1.0, material2));

    auto material3 = std::make_shared<rt::Metal>(rt::Color(0.7, 0.6, 0.5), 0.0);
    world.add(std::make_shared<rt::Sphere>(rt::Point3(4,1,0), 1.0, material3));
}

int main(int argc, char* argv[]) {
    // Camera

    rt::Camera camera;
    camera.aspect_ratio = 16.0 / 9.0;
    camera.image_width = 640;
    camera.num_pixel_samples = 50;
    camera.max_depth = 50;
    camera.vertical_fov = 20;
    camera.look_from = rt::Point3(13, 2, 3);
    camera.look_at = rt::Point3(0, 0, 0);
    camera.up_vector = rt::Vec3(0, 1, 0);
    camera.defocus_angle = 0.0;
    camera.focus_dist = 10.0;

    rt::HittableList world;
    
    populate_world(world);

    camera.render(world); // Render
    return 0;
}