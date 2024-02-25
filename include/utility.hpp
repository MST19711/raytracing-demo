#include "config.hpp"
#include "eigen-3.4.0/Eigen/Eigen"
#include "img.hpp"
#include "ray.hpp"
#include <cstdlib>
#include <random>
#include <time.h>

#ifndef UTILITY
#define UTILITY

#define MIN(x, y) (x < y ? x : y)
#define MAX(x, y) (x > y ? x : y)

color get_color(const ray &R, int depth);
inline double degrees_to_radians(double degrees) {
    return degrees * PI / 180.0;
}
inline bool in_interval(double t, interval I) {
    return I.min <= t and t <= I.max;
}
inline double random_double() { return rand() / (RAND_MAX + 1.0); }
inline double random_abs1() { return (random_double() * 2.0) - 1; }

inline direction get_reflect(const direction &R_in, const direction &norm) {
    return R_in + (-2 * (norm.normalized().dot(R_in)) * norm.normalized());
}
inline direction random_unit_vec() {
    direction R(random_abs1(), random_abs1(), random_abs1(), 0);
    while (R.norm() > 1)
        R = direction(random_abs1(), random_abs1(), random_abs1(), 0);
    return R.normalized();
}
inline direction random_unit_vec2d() {
    direction R(random_abs1(), random_abs1(), 0, 0);
    while (R.norm() > 1)
        R = direction(random_abs1(), random_abs1(), 0, 0);
    return R.normalized();
}
inline int std2int(const std::string &S) {
    int ret = 0;
    for (int i = 0; i < S.length(); i++) {
        ret += S[i] - '0';
        ret *= 10;
    }
    return ret / 10;
}
inline direction get_refraction(const direction &R_in, const direction &norm,
                                double eta, bool intoOBJ) {
    double ref_rate = intoOBJ ? (eta_air / eta) : (eta / eta_air);
    direction R_perp =
        (R_in + (-R_in.dot(norm.normalized()) * norm.normalized()));
    if (R_in.dot(R_in) - (ref_rate * R_perp).dot(ref_rate * R_perp) <= 0) {
        return direction(0, 0, 0, 0);
    }
    direction R_para =
        (R_in - R_perp).normalized() *
        (std::sqrt(
            (R_in.dot(R_in) - (ref_rate * R_perp).dot(ref_rate * R_perp))));
    return (R_para + ref_rate * R_perp).normalized();
}
#endif