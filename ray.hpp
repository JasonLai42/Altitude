#ifndef ray_hpp
#define ray_hpp

#include "vector3.hpp"


// Every ray gets a starting point (origin) and a direction ("endpoint")
class ray {
    public:
        ray() {}
        ray(const point3& ori, const vec3& dir) : origin(ori), direction(dir) {}
        
        point3 get_origin() const { return origin; }
        vec3 get_direction() const { return direction; }
        point3 point_at_parameter(double t) const { return operator+(origin, operator*(direction, t)); }

        point3 origin;
        vec3 direction;
};

#endif