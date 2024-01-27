#include "camera.hpp"
#include "ray.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <math.h>

camera::camera(ray position, direction up, double FOVW, double aspect_ratio,
               int W, int H) {
    _position = position, _up = up.normalized(), _aspect_ratio = aspect_ratio,
    _W = W, _FOVW = FOVW, _H = H;
    _next_pix = 0;
    _position.normalized();
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
    direction dir =
        _left_down_corner + (_next_pix % _W) * _dw + (_next_pix / _W) * _dh;
    _next_pix++, _next_pix %= (_W * _H);
    return std::move(ray(dir, _position.orig()));
}
bool camera::reset_nexe_pix() {
    _next_pix = 0;
    return true;
}