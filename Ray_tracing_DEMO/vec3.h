#ifndef VEC3_H
#define VEC3_H

#include<cmath>
#include<iostream>

using std::sqrt;

class vec3{
    public:
        vec3() : e{0,0,0} {}
        vec3(double e0,double e1,double e2) : e{e0,e1,e2} {}

        double x() const {return e[0]; }
        double y() const {return e[1]; }
        double z() const {return e[2]; }

        vec3 operator-() const { return vec3(-e[0],-e[1],-e[2]);}
        double operator[](int i) const { return e[i];}
        double& operator[](int i) { return e[i];}

        vec3& operator+=(const vec3 &v){
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        }
        vec3& operator-=(const vec3 &v){
            return *this += -v;
        }

        vec3& operator*=(const double t){
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }
        vec3& operator/=(const double t){
            return *this *= (1/t);
        }

        double lengthSquared() const {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }
        double length() const {
            return sqrt(this->lengthSquared());
        }
        
        double e[3];
};

using point3 = vec3;
using color = vec3;

inline std::ostream& operator<<(std::ostream &out, const vec3 &v){
    return out<<v.e[0]<<" "<<v.e[1]<<" "<<v.e[2];
}
inline vec3 operator+(const vec3 &a,const vec3 &b){
    return vec3(a.e[0]+b.e[0] , a.e[1]+b.e[1] , a.e[2]+b.e[2]);
}
inline vec3 operator-(const vec3 &a,const vec3 &b){
    return vec3(a.e[0]-b.e[0] , a.e[1]-b.e[1] , a.e[2]-b.e[2]);
}
inline vec3 operator*(const vec3 &a,const vec3 &b){
    return vec3(a.e[0]*b.e[0] , a.e[1]*b.e[1] , a.e[2]*b.e[2]);
}
inline vec3 operator*(double t,const vec3 &a){
    return vec3(a.e[0]*t , a.e[1]*t , a.e[2]*t);
}
inline vec3 operator*(const vec3 &a,double t){
    return t*a;
}
inline vec3 operator/(const vec3 &a,double t){
    return vec3(a.e[0]/t , a.e[1]/t , a.e[2]/t);
}
inline double dot(const vec3 &a,const vec3 &b){
    return a.e[0] * b.e[0] +
            a.e[1] * b.e[1] +
            a.e[2] * b.e[2];
}
inline vec3 cross(const vec3 &a,const vec3 &b){
    return vec3(a.e[1] * b.e[2] - a.e[2] * b.e[1],
                a.e[2] * b.e[0] - a.e[0] * b.e[2],
                a.e[0] * b.e[1] - a.e[1] * b.e[0]);
}
inline vec3 unitVector(const vec3 &x){
    return x/x.length();
}
#endif