#include "img.hpp"
#include "eigen-3.4.0/Eigen/Eigen"
#include <cmath>
#include <fstream>
#include <iostream>

img::img(int W, int H, std::string save_path) {
    _width = W, _height = H, _save_path = save_path;
    _buffer = new color *[W];
    for (int i = 0; i < _width; i++)
        _buffer[i] = new color[H];
} // img[W][H]
img::~img() {
    for (int i = 0; i < _width; i++)
        delete _buffer[i];
    delete _buffer;
}
color *img::operator[](int n) { return _buffer[n]; }

inline double L2G(double x) { return std::sqrt(x); }
bool img_ppm8::save() {
    std::ofstream imgout;
    imgout.open(save_path(), std::ios::out);
    std::cout << "start save img...\n";
    imgout << "P3\n" << width() << ' ' << height() << "\n255\n";
    for (int j = height() - 1; j >= 0; --j) {
        for (int i = width() - 1; i >= 0; --i) {
            int ir = static_cast<int>(255.99 * L2G((*this)[i][j].x()));
            int ig = static_cast<int>(255.99 * L2G((*this)[i][j].y()));
            int ib = static_cast<int>(255.99 * L2G((*this)[i][j].z()));

            imgout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
    std::cout << "Finish save img !!!!!\n";
    return 0;
}