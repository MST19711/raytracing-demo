#ifndef CAMERA
#define CAMERA

#include"include.h"
#include"config.h"
#include"ray.h"

class camera{
    public:
        Eigen::Vector3d updri(){return this->up;};
        point origin(){return this->CAMERA_DRI.origin;}
        camera(Eigen::Vector4d UP,Eigen::Vector4d O,Eigen::Vector4d DRI){
            this->CAMERA_DRI.direction = DRI;
            this->CAMERA_DRI.origin = O;
            this->up = UP;
        }
    private:
        ray CAMERA_DRI;
        Eigen::Vector4d up;
};

#endif