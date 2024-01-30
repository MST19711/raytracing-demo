#include "config.hpp"
#include "ray.hpp"
#include <cmath>

#ifndef HIT_RECORD
#define HIT_RECORD
class hit_record {
  public:
    hit_record(ray R_IN, point HP, direction N, double T, bool is_H)
        : ray_in(R_IN), hit_point(HP), norm(N), flying_time(T), is_hit(is_H) {}
    hit_record() {}
    ray ray_in;
    point hit_point;
    direction norm;
    double flying_time;
    bool is_hit;
};
#endif