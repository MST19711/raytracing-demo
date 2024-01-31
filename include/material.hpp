#include "config.hpp"
#include "hit_record.hpp"
#include "utility.hpp"
#include <cmath>

#ifndef MATERIAL
#define MATERIAL

class material {
  public:
    virtual color m_get_color(const hit_record &hit, int depth) = 0;
    virtual ~material() {}
};

class pure_clarity : public material {
  public:
    color m_get_color(const hit_record &hit, int depth) {
        return get_color(ray(hit.ray_in.dir(), hit.ray_in.orig()), depth);
    }
};
class mtr_norm : public material {
  public:
    color m_get_color(const hit_record &hit, int depth);
};

class mtr_simple_diffuse : public material {
  public:
    mtr_simple_diffuse(color C, int T) : _color(C), _sample_times(T) {
        _color.x() = MIN(_color.x(), 1);
        _color.y() = MIN(_color.y(), 1);
        _color.z() = MIN(_color.z(), 1);
    }
    color m_get_color(const hit_record &hit, int depth);
    ~mtr_simple_diffuse() {}

  private:
    color _color;
    int _sample_times;
};
class mtr_True_Lambertian_Reflection : public material {
  public:
    mtr_True_Lambertian_Reflection(color C, int T, double n)
        : _color(C), _sample_times(T), _n(n) {
        _color.x() = MIN(_color.x(), 1);
        _color.y() = MIN(_color.y(), 1);
        _color.z() = MIN(_color.z(), 1);
    }
    color m_get_color(const hit_record &hit, int depth);
    ~mtr_True_Lambertian_Reflection() {}

  private:
    color _color;
    int _sample_times;
    double _n;
};
class mtr_mirrored : public material {
  public:
    mtr_mirrored(color C, int T) : _color(C), _sample_times(1) {
        _color.x() = MIN(_color.x(), 1);
        _color.y() = MIN(_color.y(), 1);
        _color.z() = MIN(_color.z(), 1);
    }
    color m_get_color(const hit_record &hit, int depth);
    ~mtr_mirrored() {}

  private:
    color _color;
    int _sample_times;
};
class mtr_fuzzy_reflection : public material {
  public:
    mtr_fuzzy_reflection(color C, int T, double F)
        : _color(C), _sample_times(T), _fuzz(F < 1 ? F : 1) {
        _color.x() = MIN(_color.x(), 1);
        _color.y() = MIN(_color.y(), 1);
        _color.z() = MIN(_color.z(), 1);
    }
    color m_get_color(const hit_record &hit, int depth);
    ~mtr_fuzzy_reflection() {}

  private:
    color _color;
    int _sample_times;
    double _fuzz;
};

class mtr_refraction : public material {
  public:
    mtr_refraction(color C) : _color(C) {
        _color.x() = MIN(_color.x(), 1);
        _color.y() = MIN(_color.y(), 1);
        _color.z() = MIN(_color.z(), 1);
    }
    color m_get_color(const hit_record &hit, int depth);

  private:
    color _color;
};
#endif