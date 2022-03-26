#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct {
	SDL_Window     *win;
	SDL_Renderer   *ren;
} game;

#define blend_mode SDL_SetRenderDrawBlendMode(game.ren, SDL_BLENDMODE_BLEND);
#define normal_mode SDL_SetRenderDrawBlendMode(game.ren, SDL_BLENDMODE_NONE);

#define Rect SDL_Rect
#define FillRect(x) SDL_RenderFillRect(game.ren, &x)
#define DrawRect(x) SDL_RenderDrawRect(game.ren, &x)

#define FPoint SDL_FPoint
#define DrawLinesF(x, y) SDL_RenderDrawLinesF(game.ren, x, y);

#define DrawLineF(x1, y1, x2, y2) SDL_RenderDrawLineF(game.ren, x1, y1, x2, y2);

void set_color(color c = {0, 0, 0, 0}){
    SDL_SetRenderDrawColor(game.ren, c.r, c.g, c.b, c.a);
}
void set_scale(f scale = 1, f scale2 = 0){
	SDL_RenderSetScale(game.ren, scale, scale2?scale2:scale);
}