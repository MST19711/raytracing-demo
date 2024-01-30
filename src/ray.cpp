#include "ray.hpp"

ray::ray(Eigen::Vector4d dir, Eigen::Vector4d orig) : _dir(dir), _orig(orig) {}

Eigen::Vector4d ray::dir() const { return _dir; }
Eigen::Vector4d ray::orig() const { return _orig; }

bool ray::normalize() {
    _dir = _dir.normalized();
    return true;
}

Eigen::Vector4d ray::at(double time) const { return _dir * time + _orig; }