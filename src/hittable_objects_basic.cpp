#include "config.hpp"
#include "eigen-3.4.0/Eigen/Eigen"
#include "hittable_objects.hpp"
#include "material.hpp"

color shadeblue_sky::s_get_color(const ray &R_in) {
    Eigen::Vector4d unit_direction = R_in.dir().normalized();
    auto a = 0.5 * (unit_direction.z() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.6, 1.0);
}

world::world() { // set default world
    w_sky = new shadeblue_sky;
    H_object_list.push_back(new m_Sphere(
        point(0, -2.7, 0, 1), 0.5,
        new mtr_True_Lambertian_Reflection(color(0.5, 0, 0.5), 1, 1)));
    // H_object_list.push_back(new Sphere(point(0, -2, 0, 1), 0.5));
    H_object_list.push_back(new m_Sphere(
        point(0, -1, -100.5, 1), 100,
        new mtr_True_Lambertian_Reflection(color(0.1, 0.5, 0.1), 1, 1)));

    H_object_list.push_back(new m_Sphere(point(1, -2, 0, 1), 0.5,
                                         new mtr_mirrored(color(0.7, 0.7, 1))));

    H_object_list.push_back(
        new m_Sphere(point(-1, -2, 0, 1), 0.5,
                     new mtr_fuzzy_reflection(color(0.8, 0.8, 0.3), 1, 0.15)));

    H_object_list.push_back(new m_Sphere(
        point(-0.2, -1, 0.2, 1), 0.2,
        new mtr_Fresnel(1.33, new mtr_mirrored(color(0.8, 0.8, 0.8)),
                        new mtr_refraction(color(0.8, 0.8, 0.8), 1.33))));
}

world::~world() {
    delete w_sky;
    for (auto i : H_object_list)
        delete i;
}

hittable_object::~hittable_object() {}
sky::~sky() {}