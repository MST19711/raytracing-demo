#ifndef RAY
#define RAY

#include"include.h"
#include"config.h"

class ray{
    public:
        Eigen::Vector4d direction;
        Eigen::Vector4d origin;
};

#endif