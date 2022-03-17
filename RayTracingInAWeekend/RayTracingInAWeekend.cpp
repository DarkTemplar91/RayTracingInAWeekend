// RayTracingInAWeekend.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Color.h"
#include "Vec3.h"
#include "ray.h"

#include <iostream>


color ray_color(const ray& r) {
    vec3 unit_direction = unit_vector(r.getDirection());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}
int main()
{
    //Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 1920;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    //Camera
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_lenght = 1.0;

    auto origin = point3(0, 0, 0);
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_lenght);


    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int h = image_height - 1; h >= 0; --h) {
        std::cerr << "\rScanlines remaining: " << h << ' ' << std::flush;
        for (int w = 0; w < image_width; ++w) {
            auto u = double(w) / (image_width - 1);
            auto v = double(h) / (image_height - 1);
            ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
            color pixel_color(ray_color(r));
            write_color(std::cout, pixel_color);
        }
    }
    std::cerr << "\nDone.\n";
}


