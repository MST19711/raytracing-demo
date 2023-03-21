#ifndef OUTOUT
#define OUTPUT

#include"config.h"
#include"include.h"

void output(){
    std::ofstream outfile;
    outfile.open(outputName,std::ios::out);
    outfile<<"P3\n"<<WIDTH<<" "<<HEIGHT<<"\n255\n";
    for(int j = HEIGHT-1;j >= 0;j--){
        for(int i = 0;i < WIDTH;i++){
            outfile<<screen[j][i](0)*255.99<<" "<<screen[j][i](1)*255.99<<" "<<screen[j][i](2)*255.99<<"\n";
            //std::cout<<screen[j][i](0)<<" "<<screen[j][i](1)<<" "<<screen[j][i](2)<<"\n";
        }
    }
}

#endif