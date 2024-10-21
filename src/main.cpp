// Creating the first image.

#include "utils.hpp"
#include "hittable_list.hpp"
#include "sphere.hpp"
#include "camera.hpp"

int main(int argc, char* argv[]) {
    // Camera
    rt::Camera camera;
    camera.aspect_ratio = 16.0 / 9.0;
    camera.image_width = 400;

    // World
    rt::HittableList world;
    world.add(std::make_shared<rt::Sphere>(rt::Point3(0,-100.5,-1), 100));
    world.add(std::make_shared<rt::Sphere>(rt::Point3(0,0,-1), 0.5));

    camera.render(world); // Render
    return 0;
}