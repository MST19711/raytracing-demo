#include "camera.hpp"
#include "config.hpp"
#include "eigen-3.4.0/Eigen/Eigen"
#include "img.hpp"
#include "ray.hpp"
#include <iostream>

color get_color(ray R) {
    Eigen::Vector4d unit_direction = R.dir().normalized();
    auto a = 0.5 * (unit_direction.z() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

color draw_pixel(camera &cam) { return get_color(cam.get_next_pix()); }

img_ppm8 outputimg0(IMG_WIDTH, IMG_HEIGHT, Save_path);
camera cam0(ray(cam0dir, cam0center), cam0up, cam0FOV, cam0aspect_ratio,
            IMG_WIDTH, IMG_HEIGHT);
int main() {
    for (int j = 0; j < outputimg0.height(); j++) {
        for (int i = 0; i < outputimg0.width(); i++) {
            outputimg0[i][j] = draw_pixel(cam0);
        }
    }
    outputimg0.save();
}