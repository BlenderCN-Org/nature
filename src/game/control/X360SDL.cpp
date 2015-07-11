#include "X360SDL.h"
#include <iostream>
using namespace std;

void X360SDL::init(){
    cout<<"***gamepads:"<<SDL_NumJoysticks()<<endl;
    for(int i=0; i < SDL_NumJoysticks(); i++ ) 
    {
        printf("    %s\n", SDL_JoystickName(i));
    }
    for(int i=0;i<10;i++){
        ejes[i]=0;
    }
    if(SDL_NumJoysticks()>0){
        SDL_JoystickEventState(SDL_ENABLE);
        joystick = SDL_JoystickOpen(0);
    }
}
void X360SDL::preEventos(Personaje* p){
    ejes[0]=0;
    ejes[1]=0;

}
void X360SDL::postEventos(Personaje* p){
   p->ejesMover(ejes[0],-ejes[1]);
}
void X360SDL::manejarEvento(SDL_Event e,Personaje* p){
    switch( e.type ) {
        case SDL_JOYAXISMOTION: 
            if(e.jaxis.axis==0||e.jaxis.axis==1){
//                cout<<"axis:"<<static_cast<int>(e.jaxis.axis); 
  //              cout<<"value"<<static_cast<int>(e.jaxis.value)<<endl; 
            }
              if(e.jaxis.value<-SDL_MIN_AXIS_VALUE||e.jaxis.value>SDL_MIN_AXIS_VALUE){
                  ejes[e.jaxis.axis]=static_cast<float>(e.jaxis.value)/SDL_MAX_AXIS_VALUE;                  
              }else{
                  ejes[e.jaxis.axis]=0;                  
              }
        break;
        case SDL_JOYBUTTONDOWN:
            switch(e.jbutton.button){
                case 3:
                        p->atacar();
                    break;
                case 0:
                        p->iniciarSalto();
                    break;
            }
        //    cout<<"button:"<<static_cast<int>(e.jbutton.button)<<endl; 
        break;
        case SDL_JOYBUTTONUP:
            switch(e.jbutton.button){
                case 0:
                        p->detenerSalto();
                    break;
            }
        case SDL_JOYHATMOTION:
            //cout<<"hat:"<<static_cast<int>(e.jhat.value)<<endl; 
        break;
   }

}

