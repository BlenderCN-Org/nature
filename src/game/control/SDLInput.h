#ifndef _SDL_INPUT_H_
#define _SDL_INPUT_H_
#include "SDL/SDL.h"
#include "control/X360SDL.h"
#include "entidades/Personaje.h"
class SDLInput{
    public:
        SDLInput();
        void act(float dt,Personaje* p);
    private:
        X360SDL x360;
};
#endif

