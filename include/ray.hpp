#include "eigen-3.4.0/Eigen/Eigen"
#include "eigen-3.4.0/Eigen/src/Core/Matrix.h"

#ifndef RAY
#define RAY
class ray {
  public:
    ray() {}
    ray(Eigen::Vector4d dir, Eigen::Vector4d orig);
    Eigen::Vector4d dir();
    Eigen::Vector4d orig();
    Eigen::Vector4d at(double time);
    bool normalized();

  private:
    Eigen::Vector4d _dir, _orig;
};

#endif