#include "config.hpp"
#include "eigen-3.4.0/Eigen/Eigen"

#ifndef IMG_OUT
#define IMG_OUT

class img {
  public:
    img(int W, int H, std::string save_path);
    ~img();
    color *operator[](int n);
    int width() { return _width; }
    int height() { return _height; }
    std::string save_path() { return _save_path; }
    virtual bool save() = 0;

  private:
    int _width, _height;
    color **_buffer; // color : R, G, B
    std::string _save_path;
};

class img_ppm8 : public img {
  public:
    img_ppm8(int W, int H, std::string save_path) : img(W, H, save_path) {}
    bool save();
};
#endif