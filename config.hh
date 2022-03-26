#pragma once

using ui  = unsigned  int;
using  i  =           int;
using  f  =         float;

struct color{
    ui r;  ui g;  ui b;  ui a;
    color operator*(ui f){
        return {r*f, g*f, b*f, a*f};
    }
    color operator/(ui f){
        return {r/f, g/f, b/f, a/f};
    }
};

inline constexpr  i w        {999};
inline constexpr  i h        {999};
inline            f FOV      {0.5};
inline constexpr  f sparcity { 1 };
inline constexpr  i mw       {0xf};
inline constexpr  i mh       {0xd};
inline constexpr  i map_vis  {0xa};
inline constexpr  f mov      {0.05};
inline constexpr  f rot      {0.05};
inline constexpr  i b_size   {w/map_vis/5};
inline constexpr  i xo_mm    {b_size};
inline constexpr  i yo_mm    {h-((mw-map_vis/2 + 1)*b_size)};

inline           color bg      {   0,   0,   0, 255};
inline           color ray     { 255, 255, 255,  20};
inline           color wall    {  80,   0,   0, 200};
inline           color wall2   {   0,   0,   0, 200};
inline           color space   {   0, 255,   0, 255};
inline           color white   { 255, 255, 255, 255};
inline           color outline { 180, 180, 180, 255};