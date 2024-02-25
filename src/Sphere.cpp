#include "hittable_objects.hpp"
#include "utility.hpp"
#include <cmath>
#include <iostream>

hit_record Sphere::hit(const ray &R_in) {
    hit_record ret;
    point oc = R_in.orig() - _center;
    double a = R_in.dir().dot(R_in.dir()), b = 2.0 * oc.dot(R_in.dir()),
           c = oc.dot(oc) - (_R * _R), d = b * b - 4 * a * c;
    if (d < 0) {
        ret.is_hit = false;
        return ret;
    }
    double t0 = (-b - std::sqrt(d)) / (2.0 * a),
           t1 = (-b + std::sqrt(d)) / (2.0 * a), t;
    if (t0 >= 0 and in_interval(t0, universe))
        t = t0, ret.is_hit = true;
    else if (t1 >= 0 and in_interval(t1, universe))
        t = t1, ret.is_hit = true;
    else
        t = -1, ret.is_hit = false;
    ret.flying_time = t, ret.hit_point = R_in.at(t),
    ret.norm = (*this).get_norm_at(ret.hit_point, R_in), ret.ray_in = R_in,
    ret.intoOBJ = ((ret.hit_point - _center).dot(R_in.dir()) <= 0);
    return std::move(ret);
}

color Sphere::o_get_color(const hit_record &hit, int depth) {
    return hit.norm.segment<3>(0) + color(1, 1, 1) * 0.5;
}
point Sphere::get_hit_point(const ray &R_in, double flying_time) {
    return R_in.at(flying_time);
}
direction Sphere::get_norm_at(const point &P, const ray &R_in) {
    direction N = (P - _center).normalized();
    N.w() = 0;
    if (N.dot(R_in.dir()) > 0)
        N *= -1;
    return N.normalized();
}

color m_Sphere::o_get_color(const hit_record &hit, int depth) {
    return _mtr->m_get_color(hit, depth);
}
