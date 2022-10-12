#include<iostream>
#include<fstream>
#include "vec3.h"
#include "color.h"
#include "ray.h"


color rayColor(const ray& r){
    vec3 unitDirection = unitVector(r.direction());
    auto t = 0.5*(unitDirection.y()+1);
    return (1.0 - t)*color(1.0,1.0,1.0) + t*color(0.5,0.7,1.0);
}

int main(){
    //image
    const auto aspectRatio = 16.0/9.0;
    const int imageWidth = 400;
    const int imageHeight = static_cast<int>(imageWidth/aspectRatio);
    //camera
    auto viewpointHeight = 2.0;
    auto viewpointWidth = viewpointHeight * aspectRatio;
    auto facilLength = 1.0;
    auto orignPoint = point3(0.0,0.0,0.0);
    auto horizontal = vec3(viewpointWidth,0.0,0.0);
    auto vertical = vec3(0.0,viewpointHeight,0.0);
    auto lowerLeftCorner = orignPoint - horizontal/2 - vertical/2 -vec3(0.0,0.0,facilLength);
    //render
    std::ofstream outPutImg;
    outPutImg.open("image.ppm");
    std::cout<<"Writting image...\n";
    outPutImg<<"P3\n"<<imageWidth<<" "<<imageHeight<<"\n255\n";
    for(int j = imageHeight-1;j >= 0;j--){
        for(int i = 0;i < imageWidth;i++){
            auto u = double(i)/(imageWidth - 1);
            auto v = double(j)/(imageHeight - 1);
            ray r(orignPoint,lowerLeftCorner + u*horizontal + v*vertical);
            color pixelColor = rayColor(r);
            writeColor(outPutImg,pixelColor);
        }
    }
    outPutImg.close();
    std::cout<<"Done!";
    return 0;
}