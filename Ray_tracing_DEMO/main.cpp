#include<iostream>
#include<fstream>
#include "vec3.h"
#include "color.h"

#define IMAGE_WIDTH 256
#define IMAGE_HEIGHT 256

int main(){
    std::ofstream outPutImg;
    outPutImg.open("image.ppm");
    std::cout<<"Writting image...\n";
    outPutImg<<"P3\n"<<IMAGE_WIDTH<<" "<<IMAGE_HEIGHT<<"\n255\n";
    for(int j = IMAGE_HEIGHT-1;j >= 0;j--){
        for(int i = 0;i < IMAGE_WIDTH;i++){
            color pixelColor(double(i)/double(IMAGE_WIDTH-1),double(j)/double(IMAGE_HEIGHT-1),0.25);
            writeColor(outPutImg,pixelColor);
        }
    }
    outPutImg.close();
    std::cout<<"Done!";
    return 0;
}