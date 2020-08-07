#ifndef camera_hpp
#define camera_hpp

#include "ray.hpp"

vec3 random_in_unit_disk() {
    vec3 p;
    do {
        p = operator-(operator*(vec3(drand48(), drand48(), 0), 2.0), vec3(1, 1, 0));
    } while(dot(p, p) >= 1.0);

    return p;
}

class camera {
    public:
        camera(vec3 look_from, vec3 look_at, vec3 view_up, float v_fov, float aspect, float aperture, float focus_dist) {
            // Defocus blur var
            lens_radius = aperture / 2.0;
            // FOV var
            float theta = v_fov * M_PI / 180;
            float half_height = tan(theta / 2);
            float half_width = aspect * half_height;
            // Viewpoint var
            origin = look_from;
            w = unit_vector(operator-(look_from, look_at));
            u = unit_vector(cross(view_up, w));
            v = cross(w, u);

            lower_left_corner = operator-(operator-(operator-(origin, 
                                                    operator*(u, focus_dist * half_width)), 
                                                    operator*(v, focus_dist * half_height)), 
                                                    operator*(w, focus_dist));
            horizontal = operator*(u, 2 * focus_dist * half_width);
            vertical = operator*(v, 2 * focus_dist * half_height);
        }
        ray get_ray(float s, float t) { 
            vec3 rd = operator*(random_in_unit_disk(), lens_radius);
            vec3 offset = operator+(operator*(u, rd.get_x()), operator*(v, rd.get_y()));

            return ray(operator+(origin, offset), 
                                    operator-(operator-(operator+(operator+(lower_left_corner, 
                                                                    operator*(horizontal, s)), 
                                                                    operator*(vertical, t)), 
                                                                    origin), 
                                                                    offset));
        }

        vec3 origin;
        vec3 lower_left_corner;
        vec3 horizontal;
        vec3 vertical;
        vec3 u, v, w;
        float lens_radius;
};

#endif