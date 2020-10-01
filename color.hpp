#ifndef color_hpp
#define color_hpp

#include <iostream>

#include "vector3.hpp"


void write_color(std::ostream &out, color3 pixel_color) {
    // Write RGB values from 0 to 255
    out << static_cast<int>(pixel_color.get_x() * 255.999) << ' '
        << static_cast<int>(pixel_color.get_y() * 255.999) << ' '
        << static_cast<int>(pixel_color.get_z() * 255.999) << '\n';
}

#endif