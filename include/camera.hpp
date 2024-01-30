#include "config.hpp"
#include "eigen-3.4.0/Eigen/Eigen"
#include "ray.hpp"
#include "utility.hpp"
#include <mutex>

#ifndef CAMERA
#define CAMERA
class camera {
  public:
    camera(ray position, direction up, double FOV, double aspect_ratio, int W,
           int H);
    direction pix_w();
    direction pix_h();
    ray get_next_pix(); // left to right, down to top
    bool reset_nexe_pix();

  private:
    ray _position;
    direction _up, _dh, _dw, _left_down_corner;
    int _next_pix, _W, _H;
    double _aspect_ratio, _FOVW;
    std::mutex _nextpix_clock;
};
#endif