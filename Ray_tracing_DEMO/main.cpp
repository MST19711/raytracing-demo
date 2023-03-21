#include"include.h"
#include"config.h"
#include"output.h"
#include"ray.h"
#include"get_color.h"

ray get_ray(int h,int w){
    
}
int main(){
    for(int h = 0;h < HEIGHT;h++){
        for(int w = 0;w < WIDTH;w++){
            screen[h][w](0) = h/(double(HEIGHT));
            screen[h][w](1) = w/(double(WIDTH));
            screen[h][w](2) = 0.2;
        }
    }
    output();
    return 0;
}