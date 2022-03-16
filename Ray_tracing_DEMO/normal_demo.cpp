#include<iostream>
#include<math.h>
#include<C:\Users\CX_L\Documents\Ray_tracing_DEMO\vec3.h>
#include<C:\Users\CX_L\Documents\Ray_tracing_DEMO\ray.h>
using namespace std;

float hit_sphere(const vec3& center, float radius, const ray& r){
    vec3 oc = r.origin() - center;
    float a = r.direction().dot(r.direction());
    float b = 2.0 * oc.dot(r.direction());
    float c = oc.dot(oc) - (radius*radius);
    float dis = (b*b) - (4*a*c);
    if(dis < 0){
        return -1;
    }
    else{
        return (-b - sqrt(dis))/(2*a);
    }
}

vec3 color(ray& r){
    float T = hit_sphere(vec3(0,0,-1),0.5,r);
    if(T != -1){
        vec3 N = (r.point(T)-vec3(0,0,-1)).unit_vector();
        return (N + vec3(1,1,1))*0.5;
    }
    vec3 unit_d = r.direction().unit_vector();
    float t = 0.5*(unit_d.y() + 1.0);
    return vec3(1.0,1.0,1.0)*(1.0 - t) + vec3(0.5,0.7,1.0)*t;
}

int main(){
    freopen("test.ppm","w",stdout);
    int nx = 800,ny = 400;
    cout<<"P3\n"<<nx<<" "<<ny<<"\n255\n";
    vec3 lower_left_corner(-2.0,-1.0,-1.0);
    vec3 horizontal(4.0,0.0,0.0);
    vec3 vertical(0.0,2.0,0.0);
    vec3 origin(0.0,0.0,0.0);
    for(int j = ny-1;j >= 0;j--){
        for(int i = 0;i < nx;i++){
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);
            ray r(origin,lower_left_corner + horizontal*u + vertical*v);
            vec3 col = color(r);
            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);
            printf("%d %d %d\n",ir,ig,ib);
        }
    }
    return 0;
}

