#ifndef CONFIG
#define CONFIG

#include"include.h"
#include"camera.h"

#define WIDTH 600
#define HEIGHT 400
#define PI acos(-1)

typedef Eigen::Vector3d color;
typedef Eigen::Vector4d point;

std::string outputName = "test.ppm";
color screen[HEIGHT][WIDTH];
point cameraPoint(0.0, 0.0, 0.0, 1);
Eigen::Vector3d up(0.0, 0.0, 1.0);
double FOVH = PI/2;
Eigen::Vector4d up(0,0,1,0),center(0,0,0,0),tow(0,0,0,0);
camera cam(up,center,tow);

#endif