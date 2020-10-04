#ifndef material_hpp
#define material_hpp

#include "ray.hpp"
#include "entity.hpp"

struct hit_record;

// vec3 random_in_unit_sphere() {
//     vec3 p;
//     do {
//         p = operator-(operator*(vec3(drand48(), drand48(), drand48()), 2.0), 
//                         vec3(1, 1, 1));
//     } while(p.get_squared_magnitude() >= 1.0);

//     return p;
// }

// float schlick(float cosine, float ri) {
//     float r0 = (1 - ri) / (1 + ri);
//     r0 *= r0;
    
//     return r0 + (1 - r0) * pow((1 - cosine), 5);
// }

// class material {
//     public:
//         virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const = 0;
// };

// class lambertian : public material {
//     public:
//         lambertian(const vec3& a) : albedo(a) {}
//         virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
//             vec3 target = rec.p + rec.normal + random_in_unit_sphere();
//             scattered = ray(rec.p, target-rec.p);
//             attenuation = albedo;
            
//             return true;
//         }

//         vec3 albedo;
// };

// class metal : public material {
//     public:
//         metal(const vec3& a, float f) : albedo(a) { 
//             if(f < 1) 
//                 fuzz = f;
//             else
//                 fuzz = 1;
//         }
//         virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
//             vec3 reflected = reflect(unit_vector(r_in.get_direction()), rec.normal);
//             scattered = ray(rec.p, reflected + operator*(random_in_unit_sphere(), fuzz));
//             attenuation = albedo;
            
//             return (dot(scattered.get_direction(), rec.normal) > 0);
//         }

//         vec3 albedo;
//         float fuzz;
// };

// class dielectric : public material {
//     public:
//         dielectric(float ri) : ref_index(ri) {}
//         virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
//             vec3 outward_normal;
//             vec3 reflected = reflect(r_in.get_direction(), rec.normal);
//             float ni_over_nt;
//             attenuation = vec3(1.0, 1.0, 1.0);
//             vec3 refracted;
//             // For Schlick's approximation
//             float reflect_prob;
//             float cosine;

//             if(dot(r_in.get_direction(), rec.normal) > 0) {
//                 outward_normal = -rec.normal;
//                 ni_over_nt = ref_index;
//                 cosine = ref_index * dot(r_in.get_direction(), rec.normal) / r_in.get_direction().get_magnitude();
//             }
//             else {
//                 outward_normal = rec.normal;
//                 ni_over_nt = 1.0 / ref_index;
//                 cosine = -dot(r_in.get_direction(), rec.normal) / r_in.get_direction().get_magnitude();
//             }
            
//             if(refract(r_in.get_direction(), outward_normal, ni_over_nt, refracted)) {
//                 reflect_prob = schlick(cosine, ref_index);
//             }
//             else {
//                 reflect_prob = 1.0;
//             }

//             if(drand48() < reflect_prob) {
//                 scattered = ray(rec.p, reflected);
//             }
//             else {
//                 scattered = ray(rec.p, refracted);
//             }

//             return true;
//         }

//         float ref_index;
// };

#endif