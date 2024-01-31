#include "camera.hpp"
#include "config.hpp"
#include "eigen-3.4.0/Eigen/Eigen"
#include "hittable_objects.hpp"
#include "img.hpp"
#include "ray.hpp"
#include "utility.hpp"
#include <cmath>
#include <cstring>
#include <iostream>
#include <locale>
#include <mutex>
#include <queue>
#include <thread>
#include <time.h>

void draw_pixel(const ray &pix_ray, camera &cam, world &W, color &buffer_addr) {
    color ret(0, 0, 0);
    for (int i = 0; i < sample_per_pix; i++) {
        ret += get_color(ray(pix_ray.dir() + (cam.pix_h() * random_double()) +
                                 (cam.pix_w() * random_double()),
                             pix_ray.orig()),
                         MAX_DEPTH);
    }
    buffer_addr = ret / static_cast<double>(sample_per_pix);
}

world *main_world;
int T_number = 4;
std::queue<std::thread> T_list;

int main(int argc, char *argv[]) {

    for (int i = 0; i < argc; i++) {
        if (std::strcmp(argv[i], "-t") == 0) {
            T_number = std2int(std::string(argv[i + 1]));
        }
    }
    srand(time(0));
    time_t start_time = time(0);
    img_ppm8 outputimg0(IMG_WIDTH, IMG_HEIGHT, Save_path);
    camera cam0(ray(cam0dir, cam0center), cam0up, cam0FOV, cam0aspect_ratio,
                IMG_WIDTH, IMG_HEIGHT);
    world world0;
    main_world = &world0;
    for (int j = 0; j < outputimg0.height(); j++) {
        for (int i = 0; i < outputimg0.width(); i++) {
            ray pix_ray = cam0.get_next_pix();
#ifdef MULTI_THREAD
            if (T_list.size() >= T_number) {
                T_list.front().join();
                T_list.pop();
            }
            std::thread new_t(draw_pixel, std::move(pix_ray), std::ref(cam0),
                              std::ref(world0), std::ref(outputimg0[i][j]));
            T_list.push(std::move(new_t));
#else
            draw_pixel(pix_ray, cam0, world0,
                       outputimg0[i][j]); // single thread
#endif
        }
        while (!T_list.empty()) {
            T_list.front().join();
            T_list.pop();
        }
        std::cout << "have drawn col " << j + 1 << " / " << outputimg0.height()
                  << "...\n";
    }
    outputimg0.save();
    std::cout << "use " << time(0) - start_time << "s !!!!!\n";
    return 0;
}