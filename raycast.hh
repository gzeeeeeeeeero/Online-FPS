#pragma once

#include "game_vars.hh"

void raycaster(){
    float fov = FOV/2*M_PI;
    for(f x = 0; x <= w; x+=sparcity){
        float ind = 2*tan(fov)*x/w-tan(fov);
        vec<float> ray = {dir.x + cam.x*ind,
                          dir.y + cam.y*ind};
        vec< int > map = {int(player.x),
                          int(player.y)};
        vec<float> del = {abs(1/ray.x),
                          abs(1/ray.y)};
        vec<float> sid = {(ray.x<0?player.y-map.y:map.y+1-player.y)*del.x,
                          (ray.y<0?player.x-map.x:map.x+1-player.x)*del.y};
        int  stepX=ray.x<0?-1:1,
             stepY=ray.y<0?-1:1;
        bool hit=0, NS=0;
        while(!hit){
            if(sid.x < sid.y){
                sid.x+=del.x;
                map.y+=stepX;
                NS = 0;
            }
            else{
                sid.y+=del.y;
                map.x+=stepY;
                NS = 1;
            }
            if(MAP[map.x][map.y]) hit = 1;
        }
        float   dist;
        if(!NS) dist = sid.x - del.x;
        else    dist = sid.y - del.y;
        rays.push_back(ray*dist);
        kols.push_back((NS?-h:h)/dist);
    }
}