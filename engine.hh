#pragma once

#include "config.hh"
#include "render.hh"
#include "raycast.hh"
#include "input.hh"

void init(){

    SDL_Init(SDL_INIT_VIDEO  |
			 SDL_INIT_EVENTS |
			 SDL_INIT_TIMER  );

	IMG_Init(IMG_INIT_PNG  |
			 IMG_INIT_JPG  );
    
	game.win = SDL_CreateWindow("Contra", 
                                 SDL_WINDOWPOS_CENTERED,
                                 0,
                                 w, h, SDL_WINDOW_SHOWN |
                                 SDL_WINDOW_MOUSE_GRABBED/*|
                                 SDL_WINDOW_FULLSCREEN*/);
    SDL_ShowCursor(SDL_FALSE);
    game.ren = SDL_CreateRenderer(game.win,
                                  -1,
                                  SDL_RENDERER_ACCELERATED | 
                                  SDL_RENDERER_PRESENTVSYNC);
}

void destroy(){
    SDL_DestroyRenderer(game.ren);
    SDL_DestroyWindow  (game.win);
	IMG_Quit();
    SDL_Quit();
}

void input(){
    handleInput();
}

void update(){
    raycaster();
}

void render(){
    render_kols();
    kols.clear();
    render_map();
    render_rays();
    rays.clear();
    render_player();
    SDL_RenderPresent      (game.ren);
	SDL_SetRenderDrawColor (game.ren, bg.r, bg.g, bg.b, bg.a);
    SDL_RenderClear        (game.ren);
}
