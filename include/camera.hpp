#include "config.hpp"
#include "eigen-3.4.0/Eigen/Eigen"
#include "ray.hpp"
#include "utility.hpp"
#include <mutex>

#ifndef CAMERA
#define CAMERA
class camera {
  public:
    camera(ray position, direction up, double FOVW, double aspect_ratio, int W,
           int H);
    camera(ray position, direction up, double FOVW, double aspect_ratio, int W,
           int H, point focus_point, double defocus_angle);
    direction pix_w();
    direction pix_h();
    ray get_next_pix(); // left to right, down to top
    ray lens_blur(ray orig_ray);
    bool reset_nexe_pix();

  private:
    ray _position;
    direction _up, _dh, _dw, _left_down_corner;
    int _next_pix, _W, _H;
    double _aspect_ratio, _FOVW, _lens_blur_radios;
    std::mutex _nextpix_clock;
    point _focus_point;
};
#endif