#ifndef entity_list_hpp
#define entity_list_hpp

#include <memory>
#include <vector>

#include "entity.hpp"


using std::shared_ptr;
using std::make_shared;

class entity_list : public entity {
    public: 
        entity_list() {}
        entity_list(shared_ptr<entity> object) { add(object); }

        void clear() { objects.clear(); }
        void add(shared_ptr<entity> object) { objects.push_back(object); }

        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

        std::vector<shared_ptr<entity>> objects;
};

bool entity_list::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    hit_record temp_rec;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for(const auto& object : objects) {
        if(object->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}

#endif