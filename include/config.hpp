#include "eigen-3.4.0/Eigen/Eigen"
#include <math.h>
#include <string>

#ifndef CONFIG
#define CONFIG

const double PI = acos(-1);

typedef Eigen::Vector4d point;
typedef Eigen::Vector4d direction;

const std::string Save_path = "../test.ppm";
const int IMG_WIDTH = 800;
const auto cam0aspect_ratio = 16.0 / 9.0; // W/H
const int IMG_HEIGHT =
    std::max(static_cast<int>(IMG_WIDTH / cam0aspect_ratio), 1);

const auto viewport_height = 2.0;
const auto viewport_width =
    viewport_height * (static_cast<double>(IMG_WIDTH) / IMG_HEIGHT);

const point cam0center = Eigen::Vector4d(0, 0, 0, 1);
const direction cam0dir = Eigen::Vector4d(0, 1, 0, 0),
                cam0up = Eigen::Vector4d(0, 0, 1, 0);
const double cam0FOV = 0.5 * PI;

#endif