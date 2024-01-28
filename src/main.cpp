#include "camera.hpp"
#include "config.hpp"
#include "eigen-3.4.0/Eigen/Eigen"
#include "hittable_objects.hpp"
#include "img.hpp"
#include "ray.hpp"
#include "utility.hpp"
#include <iostream>
#include <vector>

color draw_pixel(camera &cam, world &W) {
    return get_color(cam.get_next_pix(), W);
}

int main() {
    img_ppm8 outputimg0(IMG_WIDTH, IMG_HEIGHT, Save_path);
    camera cam0(ray(cam0dir, cam0center), cam0up, cam0FOV, cam0aspect_ratio,
                IMG_WIDTH, IMG_HEIGHT);
    world world0;
    for (int j = 0; j < outputimg0.height(); j++) {
        for (int i = 0; i < outputimg0.width(); i++) {
            outputimg0[i][j] = draw_pixel(cam0, world0);
        }
    }
    outputimg0.save();
}