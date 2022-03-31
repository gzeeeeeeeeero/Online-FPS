#include "core.hh"
#include "raycast.hh"

#define sym  event.key.keysym.sym
#define mod  event.key.keysym.mod
#define mx   event.motion.x
#define typ  event.type
#define centre_mouse SDL_WarpMouseInWindow(game.win,cx,cy);

auto cx = w>>1;
auto cy = h>>1;

void rot_L(f rot){
    dir.rotate_CW(rot);
    cam.rotate_CW(rot);
}
void rot_R(f rot){
    dir.rotate_CCW(rot);
    cam.rotate_CCW(rot);
}

void handleInput(){
    auto state = SDL_GetKeyboardState(NULL);

// Top Down Controls
    if(state[SDL_SCANCODE_I]) 
        if(!MAP[int(player.x-mov)][(int)player.y])
            player.x-=mov;
            
    if(state[SDL_SCANCODE_J]) 
        if(!MAP[(int)player.x][int(player.y-mov)])
            player.y-=mov;

    if(state[SDL_SCANCODE_K])
        if(!MAP[int(player.x+mov)][(int)player.y])
            player.x+=mov;

    if(state[SDL_SCANCODE_L])
        if(!MAP[(int)player.x][int(player.y+mov)])
            player.y+=mov;

// First Person Controls
    if(state[SDL_SCANCODE_W]){
        auto to = dir;
        to.normalize();
        to*=(rot);
        if(!MAP[int(player.x+to.y)][int(player.y+to.x)]){
            player.x+=to.y;
            player.y+=to.x;
        }
    }
    if(state[SDL_SCANCODE_S]){
        auto to = dir;
        to.normalize();
        to*=(rot);
        if(!MAP[int(player.x-to.y)][int(player.y-to.x)]){
            player.x-=to.y;
            player.y-=to.x;
        }
    }
    if(state[SDL_SCANCODE_A]){
        auto to = dir;
        to.normalize();
        to*=(rot);
        to.rotate_CW(0.5);
        if(!MAP[int(player.x+to.y)][int(player.y+to.x)]){
            player.x+=to.y;
            player.y+=to.x;
        }
    }
    if(state[SDL_SCANCODE_D]){
        auto to = dir;
        to.normalize();
        to*=(rot);
        to.rotate_CCW(0.5);
        if(!MAP[int(player.x+to.y)][int(player.y+to.x)]){
            player.x+=to.y;
            player.y+=to.x;
        }
    }

// Rotations
    if(state[SDL_SCANCODE_LEFT]){
        rot_L(rot);
    }
    if(state[SDL_SCANCODE_RIGHT]){
        rot_R(rot);
    }
// FOV adjustments
    if(state[SDL_SCANCODE_UP]){
        FOV+=0.01;
    }
    if(state[SDL_SCANCODE_DOWN]){
        FOV-=0.01;
    }

    SDL_Event event;
    while(SDL_PollEvent(&event)){
        if( typ == SDL_KEYDOWN)
        if((sym == SDLK_q) && (mod & SDLK_LCTRL) ||
           (sym == SDLK_q) && (mod & SDLK_RCTRL) ||
           (sym == SDLK_ESCAPE) || typ == SDL_QUIT) exit(0);
        if( typ == SDL_MOUSEMOTION){
            if      (mx > cx) rot_R(rot/5);
            else if (mx < cx) rot_L(rot/5);
            centre_mouse
        }
    }
}