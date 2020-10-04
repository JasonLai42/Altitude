#ifndef material_hpp
#define material_hpp

#include "constants.hpp"
#include "ray.hpp"


struct hit_record;

// Schlick Approximation
double schlick(double cosine, double ref_idx) {
    auto r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;

    return r0 + (1 - r0) * pow((1 - cosine), 5);
}

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

class dielectric : public material {
    public:
        dielectric(double r_i) : ref_idx(r_i) {}

        virtual bool scatter(
            const ray& r_in, const hit_record& rec, color3& attenuation, ray& scattered
                            ) const override {
                                attenuation = color3(1.0, 1.0, 1.0);
                                double etai_over_etat = rec.front_face ? (1.0 / ref_idx) : ref_idx;

                                vec3 unit_direction = unit_vector(r_in.get_direction());

                                // Total internal reflection
                                double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
                                double sin_theta = sqrt(1.0 - (cos_theta * cos_theta));
                                if(etai_over_etat * sin_theta > 1.0) {
                                    vec3 reflected = reflect(unit_direction, rec.normal);
                                    scattered = ray(rec.p, reflected);

                                    return true;
                                }
                                // Reflectivity that varies with angle
                                double reflect_prob = schlick(cos_theta, etai_over_etat);
                                if(random_double() < reflect_prob) {
                                    vec3 reflected = reflect(unit_direction, rec.normal);
                                    scattered = ray(rec.p, reflected);

                                    return true;
                                }

                                vec3 refracted = refract(unit_direction, rec.normal, etai_over_etat);
                                scattered = ray(rec.p, refracted);

                                return true;
                            }
                            
        double ref_idx;
};

#endif