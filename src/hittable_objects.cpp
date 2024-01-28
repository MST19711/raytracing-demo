#include "hittable_objects.hpp"
#include "config.hpp"
#include "eigen-3.4.0/Eigen/Eigen"

color shadeblue_sky::get_color(ray R_in) {
    Eigen::Vector4d unit_direction = R_in.dir().normalized();
    auto a = 0.5 * (unit_direction.z() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

world::world() {
    sky = new shadeblue_sky;
    H_object_list.push_back(new empty_object);
}
world::~world() {
    delete sky;
    for (auto i : H_object_list)
        delete i;
}

hittable_object::~hittable_object() {}
sky::~sky() {}