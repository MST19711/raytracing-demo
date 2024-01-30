#include "config.hpp"
#include "eigen-3.4.0/Eigen/Eigen"
#include "eigen-3.4.0/Eigen/src/Core/Matrix.h"

#ifndef RAY
#define RAY
class ray {
  public:
    ray() {}
    ray(Eigen::Vector4d dir, Eigen::Vector4d orig);
    Eigen::Vector4d dir() const;
    Eigen::Vector4d orig() const;
    Eigen::Vector4d at(double time) const;
    bool normalize();

  private:
    Eigen::Vector4d _dir, _orig;
};

#endif