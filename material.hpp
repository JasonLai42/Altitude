#ifndef material_hpp
#define material_hpp

#include "constants.hpp"
#include "ray.hpp"


struct hit_record;

class material {
    public:
        virtual bool scatter(
            const ray& r_in, const hit_record& rec, color3& attenuation, ray& scattered
                            ) const = 0;    
};

class lambertian : public material {
    public:
        lambertian(const color3& a) : albedo(a) {}

        virtual bool scatter(
            const ray& r_in, const hit_record& rec, color3& attenuation, ray& scattered
                            ) const override {
                                vec3 scatter_direction = operator+(rec.normal, random_unit_vector());
                                scattered = ray(rec.p, scatter_direction);
                                attenuation = albedo;
                                
                                return true;
                            }
                            
        color3 albedo;
};

class metal : public material {
    public: 
        metal(const color3& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

        virtual bool scatter(
            const ray& r_in, const hit_record& rec, color3& attenuation, ray& scattered
                            ) const override {
                                vec3 reflected = reflect(unit_vector(r_in.get_direction()), rec.normal);
                                scattered = ray(rec.p, operator+(reflected, operator*(random_in_unit_sphere(), fuzz)));
                                attenuation = albedo;

                                return (dot(scattered.get_direction(), rec.normal) > 0);
                            }

        color3 albedo;
        // The larger the object, the more fuzzy it becomes
        double fuzz;
};

#endif