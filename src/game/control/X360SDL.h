#ifndef _X360SDL_H_
#define _X360SDL_H_
#include "SDL/SDL.h"
#include "entidades/Personaje.h"
const float SDL_MAX_AXIS_VALUE=32768;
const float SDL_MIN_AXIS_VALUE=6000;
class X360SDL{
    public:
        void init();
        void preEventos(Personaje* p);
        void manejarEvento(SDL_Event e,Personaje* p);
        void postEventos(Personaje* p);
    private:
        SDL_Joystick *joystick;
        float ejes[10];

};
#endif

