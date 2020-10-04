#ifndef camera_hpp
#define camera_hpp

#include "constants.hpp"
#include "vector3.hpp"
#include "ray.hpp"


class camera {
    public:
        camera(
            point3 look_from, point3 look_at, vec3 vup, double v_fov, double aspect_ratio, double aperture, double focus_dist
              ) {
            // Camera can shoot rays to whatever plane we want (z = -1 or -2, etc) as long as it 
            // is proportionate to h (height of viewport on one side of axis)
            auto theta = degrees_to_radians(v_fov);
            auto h = tan(theta / 2);
            auto viewport_height = 2.0 * h;
            auto viewport_width = aspect_ratio * viewport_height;

            w = unit_vector(look_from - look_at);
            u = unit_vector(cross(vup, w));
            v = cross(w, u);

            origin = look_from;
            horizontal = operator*(u, focus_dist * viewport_width);
            vertical = operator*(v, focus_dist * viewport_height);
            lower_left_corner = operator-(
                                    operator-(
                                        operator-(origin, operator/(horizontal, 2)), 
                                                                    operator/(vertical, 2)), 
                                                                                    operator*(w, focus_dist));
        
            lens_radius = aperture / 2;
        }

        // Function get rays that start from origin and shoot into each pixel
        ray get_ray(double s, double t) const {
            vec3 rd = operator*(random_in_unit_disk(), lens_radius);
            vec3 offset = (u * rd.get_x()) + (v * rd.get_y());

            return ray(operator+(origin, offset), 
                        operator-(
                            operator-(
                                operator+(
                                    operator+(lower_left_corner, operator*(horizontal, s)), 
                                                                    operator*(vertical, t)), 
                                                                            origin), 
                                                                                offset));
        }

    private:
        point3 origin;
        point3 lower_left_corner;
        vec3 horizontal;
        vec3 vertical;
        vec3 u, v, w;
        double lens_radius;
};

#endif