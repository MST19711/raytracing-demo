#include "eigen-3.4.0/Eigen/Eigen"
#include "hittable_objects.hpp"
#include "img.hpp"
#include "ray.hpp"

#ifndef UTILITY
#define UTILITY
color get_color(ray R, world &W);
bool load_world(world &W);
#endif