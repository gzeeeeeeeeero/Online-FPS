#include "engine.hh"

int main(){
    
    atexit(destroy);
    init();

    while(!!1){
        input ();
        update();
        render();
        SDL_Delay(17);
    }

    return 0x0;
}