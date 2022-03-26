#pragma once

#include "core.hh"
#include "map.hh"
#include "raycast.hh"

#define __   b_size
#define _  * b_size
#define s  / scale

int u=0, l=0, vis = map_vis>>1, ub = map_vis*b_size;

void render_kols(){
    {
        f x = 0; i i = 0;
        for(; x <= w; x+=sparcity, i++){
            if(kols[i] > 0) set_color(white);
            else            set_color(white/3);
            auto st = -abs(kols[i])/2 + h/2;
            if(st < 0) st = 0;
            auto en =  abs(kols[i])/2 + h/2;
            if(en >= w) en = h-1;
            DrawLineF(x, st, x, en);
        }
    }
}

void __render_rays(f x1, f y1, vector<vec<float>> rays){
    float y11 = (y1 - l) _;
    float x11 = (x1 - u) _;
    for(auto i = 0; i < rays.size(); i ++){
        float x22 = (y1 + rays[i].x - l) _;
        float y22 = (x1 + rays[i].y - u) _;
        if(x22 < 0) x22 = 0;
        if(y22 < 0) y22 = 0;
        if(x22 > ub) x22 = ub;
        if(y22 > ub) y22 = ub;
        DrawLineF(
                    xo_mm + y11,
                    yo_mm + x11,
                    xo_mm + x22,
                    yo_mm + y22
                 );
    }
}

void render_rays(){
    set_color(ray);
    blend_mode
    __render_rays(player.x, player.y, rays);
    normal_mode
}

void render_player(){
    auto scale = 2;

    vec<float> foot = dir;
    foot.normalize();
    foot.rotate_CW(0.5);
    foot*=(0.08);

    vec<float> legg = dir;
    legg.normalize();
    legg*=(0.3);

    set_scale(scale);
    set_color(white);
    FPoint points[] = {
                            {
                                (xo_mm + (player.y + foot.x - l)_) s,
                                (yo_mm + (player.x + foot.y - u)_) s
                            },
                            {
                                (xo_mm + (player.y - foot.x - l)_) s,
                                (yo_mm + (player.x - foot.y - u)_) s
                            },
                            {
                                (xo_mm + (player.y + legg.x - l)_) s,
                                (yo_mm + (player.x + legg.y - u)_) s
                            },
                                 points[0]
                        };
    DrawLinesF(points, 4);
    set_scale();
}

void render_map(){
    int
    x = player.x,
    y = player.y,
    i1=0, i2=mw ,
    j1=0, j2=mh ;

    i1 = x-vis;
    i2 = x+vis;
    if(i1 < 0 ){i2-=i1;i1=0;}
    if(i2 > mw){i1-=i2-mw;i2=mw;}

    j1 = y-vis;
    j2 = y+vis;
    if(j1 < 0 ){j2-=j1;j1=0;}
    if(j2 > mh){j1-=j2-mh;j2=mh;}

    if((x-vis) >= 0 && ((x-vis) < (vis+1))) u = (x-vis);
    if((y-vis) >= 0 && ((y-vis) < (vis-1))) l = (y-vis);
    
    for(int i = i1;
            i < i2; i++){
    for(int j = j1;
            j < j2; j++){
            Rect block = {xo_mm + int((j-j1) _),
                          yo_mm + int((i-i1) _),
                          __, __};
            if(MAP[i][j] == 0){
              set_color(space);
              DrawRect(block);
            }
            else if(MAP[i][j] == 3){
                set_color(space);
                FillRect(block);
            }
            else{
              blend_mode
              set_color(wall);
              FillRect(block);
              normal_mode
              set_color(wall2);
              DrawRect(block);
            }
        }
    }
    set_color(outline);
    Rect block = {xo_mm - 1,
                  yo_mm - 1,
                  map_vis _ +1,
                  map_vis _ +1};
    DrawRect(block);
}
