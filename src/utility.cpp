#include "utility.hpp"
#include "config.hpp"
#include "hit_record.hpp"
#include "hittable_objects.hpp"
#include <cmath>
#include <cstdlib>
#include <iostream>

color get_color(const ray &R, int depth) {
    if (depth <= 0)
        return color(0, 0, 0);
    Eigen::Vector4d unit_direction = R.dir().normalized();
    auto a = 0.5 * (unit_direction.z() + 1.0);
    hittable_object *nearestOBJ = nullptr;
    hit_record nearest_hit;
    nearest_hit.flying_time = DBL_MAX;
    for (auto i : main_world->H_object_list) {
        hit_record this_hit = i->hit(R);
        if (this_hit.flying_time < nearest_hit.flying_time and
            this_hit.is_hit) {
            nearest_hit = this_hit;
            nearestOBJ = i;
        }
    }
    if (nearestOBJ != nullptr)
        return nearestOBJ->o_get_color(nearest_hit, depth - 1);
    else
        return main_world->sky->s_get_color(R);
}
// bool load_world(world &W) {}
