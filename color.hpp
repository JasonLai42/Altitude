#ifndef color_hpp
#define color_hpp

#include <iostream>

#include "vector3.hpp"


void write_color(std::ostream &out, color3 pixel_color, int samples_per_pixel) {
    auto r = pixel_color.get_x();
    auto g = pixel_color.get_y();
    auto b = pixel_color.get_z();

    // Divide color by the number of samples
    auto scale = 1.0 / samples_per_pixel;
    r *= scale;
    g *= scale;
    b *= scale;

    // Write RGB values from 0 to 255
    out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}

#endif