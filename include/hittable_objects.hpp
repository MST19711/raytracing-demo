#include "config.hpp"
#include "hit_record.hpp"
#include "img.hpp"
#include "material.hpp"
#include "ray.hpp"
#include "utility.hpp"
#include <vector>

#ifndef HITTABLE
#define HITTABLE
class world;
class hittable_object {
  public:
    virtual hit_record hit(const ray &R_in) = 0;
    // virtual point get_hit_point(const ray &R_in) = 0;
    virtual color o_get_color(const hit_record &hit, int depth) = 0;
    virtual ~hittable_object() = 0;
};
class sky {
  public:
    virtual color s_get_color(const ray &R_in) = 0;
    virtual ~sky() = 0;
};
class world {
  public:
    world();
    ~world();
    sky *w_sky;
    std::vector<hittable_object *> H_object_list;
};
extern world *main_world;
//  utilities

bool load_world(world &W);
// skys
class shadeblue_sky : public sky {
  public:
    color s_get_color(const ray &R_in);
    ~shadeblue_sky() {}
};

// objs
class empty_object : public hittable_object {
  public:
    ~empty_object() {}
    hit_record hit(const ray &R_in) {
        return hit_record(ray(direction(0, 0, 0, 0), point(0, 0, 0, 0)),
                          point(0, 0, 0, 0), direction(0, 0, 0, 0), -1, false);
    }
    color o_get_color(const hit_record &hit, int depth) {
        return color(0, 0, 0);
    }
    point get_hit_point(const ray &R_in) { return point(0, 0, 0, 0); }
};
// Sphere
class Sphere : public hittable_object {
  public:
    ~Sphere() {}
    Sphere(point C, double R) : _center(C), _R(R) {}
    hit_record hit(const ray &R_in);
    direction get_norm_at(const point &P, const ray &R_in);
    color o_get_color(const hit_record &hit, int depth);
    point get_hit_point(const ray &R_in, double flying_time);
    point center() { return _center; }
    double R() { return _R; }

  private:
    point _center;
    double _R;
};
class m_Sphere : public Sphere {
  public:
    m_Sphere(point C, double R, material *M) : Sphere(C, R), _mtr(M) {}
    color o_get_color(const hit_record &hit, int depth);
    ~m_Sphere() { delete _mtr; }

  private:
    material *_mtr;
};

class hollow_Sphere : public hittable_object {
  public:
    hollow_Sphere(point C, double R_out, double R_in, material *M)
        : _out_sph(new Sphere(C, R_out)), _in_sph(new Sphere(C, R_in)){};
    ~hollow_Sphere() {
        delete _out_sph;
        delete _in_sph;
        delete _mtr;
    }
    hit_record hit(const ray &R_in);
    color o_get_color(const hit_record &hit, int depth);

  private:
    Sphere *_out_sph, *_in_sph;
    material *_mtr;
};
#endif