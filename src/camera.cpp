#include "camera.hpp"
#include "ray.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <math.h>
#include <mutex>
#include <thread>
#include <utility>

camera::camera(ray position, direction up, double FOVW, double aspect_ratio,
               int W, int H) {
    _position = position, _up = up.normalized(), _aspect_ratio = aspect_ratio,
    _W = W, _FOVW = FOVW, _H = H;
    _up -= _position.dir().normalized().dot(_up) * _position.dir().normalized();
    _up = _up.normalized();
    _next_pix = 0;
    _position.normalize();
    double dx = std::tan(_FOVW / 2.0) * (2.0 / (static_cast<double>(W)));
    Eigen::Vector3d up3d = _up.segment<3>(0),
                    dir3d = _position.dir().segment<3>(0),
                    dw3d = dir3d.cross(up3d).normalized();
    _dw.segment<3>(0) = dw3d * dx;
    _dh = _up * dx;
    _focus_point = _position.orig() + position.dir();
    _lens_blur_radios = 0;
    _left_down_corner = _position.dir() - (_W / 2.0) * _dw - (_H / 2.0) * _dh;
}
camera::camera(ray position, direction up, double FOVW, double aspect_ratio,
               int W, int H, point focus_point, double defocus_angle) {
    _position = position, _up = up.normalized(), _aspect_ratio = aspect_ratio,
    _W = W, _FOVW = FOVW, _H = H, _focus_point = focus_point;
    double focus_dist = _position.dir().segment<3>(0).normalized().dot(
        (_focus_point - _position.orig()).segment<3>(0));
    _lens_blur_radios = std::tan(defocus_angle / 2) * focus_dist;
    double t =
        ((_focus_point - _position.orig())
             .segment<3>(0)
             .dot(_position.dir().segment<3>(0))) /
        (_position.dir().segment<3>(0).dot(_position.dir().segment<3>(0)));
    _position = ray(_position.dir() * t, _position.orig());
    _up -= _position.dir().normalized().dot(_up) * _position.dir().normalized();
    _up = _up.normalized();
    _next_pix = 0;
    double dx = std::tan(_FOVW / 2.0) * (2.0 / (static_cast<double>(W)));
    Eigen::Vector3d up3d = _up.segment<3>(0),
                    dir3d = _position.dir().segment<3>(0),
                    dw3d = dir3d.cross(up3d).normalized();
    _dw.segment<3>(0) = dw3d * dx;
    _dh = _up * dx;
    _left_down_corner = _position.dir() - (_W / 2.0) * _dw - (_H / 2.0) * _dh;
}
direction camera::pix_w() { return _dw; }
direction camera::pix_h() { return _dh; }
ray camera::get_next_pix() {
    //_nextpix_clock.lock();
    direction dir =
        _left_down_corner + (_next_pix % _W) * _dw + (_next_pix / _W) * _dh;
    _next_pix++, _next_pix %= (_W * _H);
    //_nextpix_clock.unlock();
    return std::move(ray(dir, _position.orig()));
}
ray camera::lens_blur(ray orig_ray) {
    direction random_bulr_vec = random_unit_vec2d();
    random_bulr_vec = random_bulr_vec.x() * _dh + random_bulr_vec.y() * _dw;
    random_bulr_vec.w() = 0;
    random_bulr_vec = random_bulr_vec.normalized();
    random_bulr_vec *= _lens_blur_radios;
    return std::move(ray(orig_ray.dir() - random_bulr_vec,
                         orig_ray.orig() + random_bulr_vec));
}
bool camera::reset_nexe_pix() {
    _next_pix = 0;
    return true;
}