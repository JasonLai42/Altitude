#ifndef sphere_hpp
#define sphere_hpp

#include "vector3.hpp"
#include "entity.hpp"


class sphere : public entity {
    public:
        sphere() {}
        sphere(point3 c, double r) : center(c), radius(r) {}

        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
        
        point3 center;
        double radius;
        material* mat_ptr;
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    // Vector oc is vector from ray origin to sphere's center
    vec3 oc = r.get_origin() - center;
    // Get simplified components of quadratic equation for (P(t) - C)^2 = r^2
    auto a = r.get_direction().get_squared_magnitude();
    auto b_halved = dot(oc, r.get_direction());
    auto c = oc.get_squared_magnitude() - (radius * radius);
    // Find number of solutions (hits)
    auto discriminant = (b_halved * b_halved) - (a * c);

    // Check for hits
    if(discriminant > 0) {
        auto root = sqrt(discriminant);

        // Check interval for valid hit for - version of quadratic formula
        auto temp = (-b_halved - root) / a;
        if(temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);
            return true;
        }
        
        // Check interval for valid hit for + version of quadratic formula
        temp = (-b_halved + root) / a;
        if(temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);
            return true;
        }
    }

    return false;
}

#endif