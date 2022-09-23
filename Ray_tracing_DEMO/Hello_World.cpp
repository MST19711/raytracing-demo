#include<iostream>
#include"vec3.h"
using namespace std;
int main(){
    freopen("Hello_World.ppm","w",stdout);
    int nx = 400,ny = 300;
    cout<<"P3\n"<<nx<<" "<<ny<<"\n255\n";
    for(int j = ny-1;j >= 0;j--){
        for(int i = 0;i < nx;i++){
            vec3 color(float(i) / float(nx),float(j) / float(ny),0.2);
            int ir = int(255.99 * color.x());
            int ig = int(255.99 * color.y());
            int ib = int(255.99 * color.z());
            printf("%d %d %d\n",ir,ig,ib);
        }
    }
    return 0;
}