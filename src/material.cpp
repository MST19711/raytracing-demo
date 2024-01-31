#include "material.hpp"
#include "eigen-3.4.0/Eigen/Eigen"
#include "utility.hpp"
#include <iostream>
#include <random>
#include <time.h>

color mtr_norm::m_get_color(const hit_record &hit, int depth) {
    return (hit.norm.segment<3>(0) + color(1, 1, 1)) * 0.5;
}

void use_color(const color &C, color &RET) {
    RET.x() *= C.x();
    RET.y() *= C.y();
    RET.z() *= C.z();
}
color mtr_simple_diffuse::m_get_color(const hit_record &hit, int depth) {
    color ret_color(0, 0, 0);
    for (int i = 0; i < _sample_times; i++) {
        Eigen::Vector4d R(random_abs1(), random_abs1(), random_abs1(), 0);
        while (R.norm() > 1)
            R = Eigen::Vector4d(random_abs1(), random_abs1(), random_abs1(), 0);
        if (R.dot(hit.norm) < 0)
            R *= -1;
        ret_color += get_color(ray(R, hit.hit_point), depth);
    }
    ret_color /= _sample_times;
    use_color(_color, ret_color);
    return ret_color;
}

color mtr_True_Lambertian_Reflection::m_get_color(const hit_record &hit,
                                                  int depth) {
    color ret_color(0, 0, 0);
    for (int i = 0; i < _sample_times; i++) {
        direction R = random_unit_vec() + (hit.norm.normalized() * _n);
        ret_color += get_color(ray(R, hit.hit_point), depth);
    }
    ret_color /= _sample_times;
    use_color(_color, ret_color);
    return ret_color;
}

color mtr_mirrored::m_get_color(const hit_record &hit, int depth) {
    color ret_color(0, 0, 0);
    ret_color += get_color(
        ray(get_reflect(hit.ray_in.dir(), hit.norm), hit.hit_point), depth);
    use_color(_color, ret_color);
    return ret_color;
}
color mtr_fuzzy_reflection::m_get_color(const hit_record &hit, int depth) {
    color ret_color(0, 0, 0);
    direction D = get_reflect(hit.ray_in.dir(), hit.norm).normalized() +
                  _fuzz * random_unit_vec();
    if (D.dot(hit.norm) <= 0) {
        D -= 2 * hit.norm * (D.dot(hit.norm.normalized()));
    }
    ret_color += get_color(ray(D, hit.hit_point), depth);
    use_color(_color, ret_color);
    return ret_color;
}