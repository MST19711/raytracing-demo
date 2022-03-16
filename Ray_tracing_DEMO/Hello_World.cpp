#include<iostream>
#include<C:\Users\CX_L\Documents\Ray_tracing_DEMO\vec3.h>
using namespace std;
int main(){
    freopen("Hello_World.ppm","w",stdout);
    int nx = 400,ny = 300;
    cout<<"P3\n"<<nx<<" "<<ny<<"\n255\n";
    for(int j = ny-1;j >= 0;j--){
        for(int i = 0;i < nx;i++){
            vec3 color(float(i) / float(nx),float(j) / float(ny),0.2);
            int ir = int(255.99 * color.r());
            int ig = int(255.99 * color.g());
            int ib = int(255.99 * color.b());
            printf("%d %d %d\n",ir,ig,ib);
        }
    }
    return 0;
}