// RayTracingInAWeekend.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "util_funcs.h"
#include "Color.h"
#include "Vec3.h"
#include "ray.h"
#include "hittable_list.h"
#include "hittable.h"
#include "sphere.h"
#include "camera.h"

#include <iostream>

double hit_sphere(const point3& center, double radius, const ray& r) {
    vec3 oc = r.origin() - center;
    auto a = r.direction().lengt_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.lengt_squared() - (radius * radius);
    auto discriminant = half_b*half_b - 4*a*c;
    if (discriminant < 0)
        return -1.0;;
    return(-half_b - sqrt(discriminant)) / a;
}

color ray_color(const ray& r, const hittable& world, int depth) {
    hit_record rec;

    if (depth <= 0)
        return color(0, 0, 0);

    if (world.hit(r,0.001,infinity,rec)) {
        point3 target = rec.p + rec.normal + random_unit_vector();
        return 0.5 * ray_color(ray(rec.p, target - rec.p), world, depth - 1);
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}
int main()
{
    //Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 480;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel=100;
    const int max_depth = 50;

    //World
    hittable_list world;
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

    //Camera
    camera cam;

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int h = image_height - 1; h >= 0; --h) {
        std::cerr << "\rScanlines remaining: " << h << ' ' << std::flush;
        for (int w = 0; w < image_width; ++w) {
            color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; s++) {
                auto u = (w+random_double())/(image_width-1);
                auto v = (h+random_double()) / (image_height - 1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world,max_depth);

            }
            
            write_color(std::cout, pixel_color,samples_per_pixel);
        }
    }
    std::cerr << "\nDone.\n";
}


