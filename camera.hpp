#ifndef camera_hpp
#define camera_hpp

#include "constants.hpp"
#include "vector3.hpp"
#include "ray.hpp"


class camera {
    public:
        camera(point3 look_from, point3 look_at, vec3 vup, double v_fov, double aspect_ratio) {
            // Camera can shoot rays to whatever plane we want (z = -1 or -2, etc) as long as it 
            // is proportionate to h (height of viewport on one side of axis)
            auto theta = degrees_to_radians(v_fov);
            auto h = tan(theta / 2);
            auto viewport_height = 2.0 * h;
            auto viewport_width = aspect_ratio * viewport_height;

            auto w = unit_vector(look_from - look_at);
            auto u = unit_vector(cross(vup, w));
            auto v = cross(w, u);

            origin = look_from;
            horizontal = operator*(u, viewport_width);
            vertical = operator*(v, viewport_height);
            lower_left_corner = operator-(
                                    operator-(
                                        operator-(origin, operator/(horizontal, 2)), 
                                                                        operator/(vertical, 2)), 
                                                                                        w);
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