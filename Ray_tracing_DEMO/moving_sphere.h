#ifndef MOVING_SPHERE_H
#define MOVING_SPHERE_H

#include "common.h"
#include "hitable.h"

class moving_sphere{
    private:
        point3 center0, center1;
        double time0, time1;
        double raduis;
        shared_ptr<material> mat_ptr;
};

#endif