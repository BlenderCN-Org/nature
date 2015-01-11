#ifndef _PERSONAJE_H_
#define _PERSONAJE_H_
#include "Entidad.h"


class Personaje:public Entidad{
    public:
    enum class Estado{
       Caminando,
       Corriendo,
       Parado,
       Saltando,
       Cayendo
    };
   Estado estado;
   virtual void act(float dt);
   void iniciarSalto();
   void detenerSalto();
   void ejesMover(float x,float y);

};
#endif

