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

inline direction get_reflect(direction R_in, direction norm) {
    return R_in + (-2 * (norm.normalized().dot(R_in)) * norm.normalized());
}
inline direction random_unit_vec() {
    direction R(random_abs1(), random_abs1(), random_abs1(), 0);
    while (R.norm() > 1)
        R = direction(random_abs1(), random_abs1(), random_abs1(), 0);
    return R.normalized();
}
inline int std2int(std::string S) {
    int ret = 0;
    for (int i = 0; i < S.length(); i++) {
        ret += S[i] - '0';
        ret *= 10;
    }
    return ret / 10;
}
#endif