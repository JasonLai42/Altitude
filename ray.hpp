#ifndef ray_hpp
#define ray_hpp

#include "vector.hpp"

class ray {
    public:
        ray() {}
        ray(const vec3& a, const vec3& b) { origin = a; direction = b; }
        vec3 get_origin() const { return origin; }
        vec3 get_direction() const { return direction; }
        vec3 point_at_parameter(float t) const { return operator+(origin, operator*(direction, t)); }

        vec3 origin;
        vec3 direction;
};

#endif