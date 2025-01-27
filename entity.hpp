#ifndef entity_hpp
#define entity_hpp

#include "constants.hpp"
#include "ray.hpp"


// Let the compiler know the pointer in the struct is to a class
class material;

struct hit_record {
    double t;
    point3 p;
    vec3 normal;
    bool front_face;
    // Used to point at the material pointer an entity e.g. a sphere is given in the main
    // When ray_color routine gets an entity's hit_record, it can call member functions of 
    // the material pointer to figure out how to scatter the ray
    shared_ptr<material> mat_ptr;

    // We have normals always point outward to determine which side of the 
    // surface the ray is coming from at geometry time (vs. always pointing 
    // against ray to determine at coloring time)
    inline void set_face_normal(const ray& r, const vec3& outward_normal) {
        front_face = dot(r.get_direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class entity {
    public:
        // t_min and t_max for valid hit interval
        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};

#endif