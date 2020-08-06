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

vec3 reflect(const vec3& v, const vec3& n) {
    return operator-(v, (operator*(n, 2 * dot(v, n))));
}

bool refract(const vec3& v, const vec3& n, float ni_over_nt, vec3& refracted) {
    vec3 uv = unit_vector(v);
    float dt = dot(uv, n);
    float discriminant = 1.0 - (ni_over_nt * ni_over_nt * (1 - (dt * dt)));

    if(discriminant > 0) {
        refracted = operator-(operator*(operator-(uv, operator*(n, dt)), ni_over_nt), 
                                operator*(n, sqrt(discriminant)));
        
        return true;
    }
    else 
        return false;
}

#endif