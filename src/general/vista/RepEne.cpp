#include "RepEne.h"

void RepEne::act(float dt){
        Monstruo* p= (Monstruo*) ent.get();
        switch(p->estado){
            case Monstruo::Estado::Detenido:
               ani->animar("caminar",true);
           break;
           case Monstruo::Estado::Caminando:
               ani->animar("caminar",true);
           break;
           case Monstruo::Estado::AtaqueBomba:
               ani->animar("ataqueBomba",false,false);
           break;
           case Monstruo::Estado::AtaqueGirar:
               ani->animar("ataqueGirar",false,false);
           break;
           case Monstruo::Estado::Herido:
               ani->animar("herido",true);
           break;
           case Monstruo::Estado::Encerrado:
               ani->animar("encerrado");
           break;
           case Monstruo::Estado::Muerto:
               ani->animar("morir",false,false);
           break;
       }
       if(ani->actual()==ani->id("ataqueGirar")&&ani->terminado()) 
           p->detener();
       ani->act(dt);
}

