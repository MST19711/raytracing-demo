#include "utility.hpp"

color get_color(ray R, world &W) {
    Eigen::Vector4d unit_direction = R.dir().normalized();
    auto a = 0.5 * (unit_direction.z() + 1.0);
    for (auto i : W.H_object_list) {
        if (i->hit(R)) {
            return i->get_color(R);
        }
    }
    return W.sky->get_color(R);
}
// bool load_world(world &W) {}