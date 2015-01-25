#include "RepPer.h"
using namespace std;
void RepPer::act(float dt){
        Personaje* p= (Personaje*) ent.get();
        switch(p->estado){
           case Personaje::Estado::Caminando:
               ani->animar("caminar",true);
           break;
           case Personaje::Estado::Saltando:
               ani->animar("saltar",true);
           break;
           case Personaje::Estado::Cayendo:
               ani->animar("caer",true);
           break;
           case Personaje::Estado::Corriendo:
               ani->animar("correr",true);
           break;
           case Personaje::Estado::Parado:
               ani->animar("parado",true);
           break;
           case Personaje::Estado::Herir:
               ani->animar("herir",true);
           break;
           case Personaje::Estado::Muerto:
               ani->animar("herir",false);
           break;
           case Personaje::Estado::Atacando:
                if(ani->terminado()){
                    p->detener();
                }else{
                   ani->animar("atacar",false);
                }
           break;
       }
       ani->act(dt);
}

