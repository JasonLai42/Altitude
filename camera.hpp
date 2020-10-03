#ifndef camera_hpp
#define camera_hpp

#include "constants.hpp"


class camera {
    public:
        camera() {
            // Redundant? Consider changing later
            auto aspect_ratio = ASPECT_RATIO;
            auto viewport_height = VWPORT_HEIGHT;
            auto viewport_width = VWPORT_WIDTH;
            auto focal_length = FOCAL_LENGTH;

            origin = point3(0, 0, 0);
            horizontal = vec3(viewport_width, 0.0, 0.0);
            vertical = vec3(0.0, viewport_height, 0.0);
            lower_left_corner = operator-(
                                    operator-(
                                        operator-(origin, operator/(horizontal, 2)), 
                                                                operator/(vertical, 2)), 
                                                                    vec3(0, 0, focal_length));
        }

        // Function get rays that start from origin and shoot into each pixel
        ray get_ray(double u, double v) const {
            return ray(origin, operator-(
                                    operator+(
                                        operator+(lower_left_corner, operator*(horizontal, u)), 
                                                                            operator*(vertical, v)), 
                                                                                origin));
        }

    private:
        point3 origin;
        point3 lower_left_corner;
        vec3 horizontal;
        vec3 vertical;
};

#endif