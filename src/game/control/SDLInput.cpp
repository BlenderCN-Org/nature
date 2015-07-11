#include "SDLInput.h"
SDLInput::SDLInput(){
    x360.init();
}
void SDLInput::act(float dt,Personaje* p){
    SDL_Event event;
    //x360.preEventos(p);
    while(SDL_PollEvent(&event)){
        if(event.type==SDL_KEYDOWN&&event.key.keysym.sym==SDLK_ESCAPE){
            SDL_Quit();
            exit(0);
        }
        x360.manejarEvento(event,p);
    }
    x360.postEventos(p);
        
}
