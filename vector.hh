#pragma once

#include <ios>
#include <math.h>
#include <ostream>

template <typename T>
struct vec {
    T x;
    T y;
    vec<T>  operator+ (const vec<T>& b){
        return {x + b.x, y + b.y};
    }
    vec<T>  operator- (const vec<T>& b){
        return {x - b.x, y - b.y};
    }
    vec<T>  operator* (const float& factor){
        return {x * factor, y * factor};
    }
    vec<T>  operator/ (const float& factor){
        return {x / factor, y / factor};
    }
    vec<T>& operator+=(const vec<T>& b){
        x += b.x;
        y += b.y;
        return *this;
    }
    vec<T>& operator-=(const vec<T>& b){
        x -= b.x;
        y -= b.y;
        return *this;
    }
    vec<T>& operator*=(const float& factor){
        x *= factor;
        y *= factor;
        return *this;
    }
    vec<T>& operator/=(const float& factor){
        x /= factor;
        y /= factor;
        return *this;
    }
    inline float magnitude(){
        return sqrt(x*x + y*y);
    }
    inline void normalize(){
        *this*=1/magnitude();
    }
    void rotate_CCW(float rad){
        rad*=M_PI;
        float c = cos(rad);
        float s = sin(rad);
        T _x = x, _y = y;
        x =  c*_x - s*_y;
        y =  s*_x + c*_y;
    }
    void rotate_CW(float rad){
        rotate_CCW(-rad);
    }
};
template <typename T>
std::ostream& operator<<(std::ostream& os, const vec<T>& v){
    return os << "\033[1;31m" << "[" << "\033[0m"
              << "\033[1;32m" << v.x << "\033[0m"
              << "  "
              << "\033[1;32m" << v.y << "\033[0m"
              << "\033[1;31m" << "]" << "\033[0m";
}