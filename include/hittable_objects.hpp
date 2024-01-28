#include "config.hpp"
#include "img.hpp"
#include "ray.hpp"
#include <vector>

#ifndef HITTABLE
#define HITTABLE
class hittable_object {
  public:
    virtual bool hit(ray R_in) = 0;
    virtual color get_color(ray R_in) = 0;
    virtual ~hittable_object() = 0;
};
class sky {
  public:
    virtual color get_color(ray R_in) = 0;
    virtual ~sky() = 0;
};
class world {
  public:
    world();
    ~world();
    sky *sky;
    std::vector<hittable_object *> H_object_list;
};

class shadeblue_sky : public sky {
  public:
    color get_color(ray R_in);
    ~shadeblue_sky() {}
};
class empty_object : public hittable_object {
  public:
    ~empty_object() {}
    bool hit(ray R_in) { return false; }
    color get_color(ray R_in) { return color(0, 0, 0); }
};
#endif