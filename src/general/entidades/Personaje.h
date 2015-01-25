#ifndef _PERSONAJE_H_
#define _PERSONAJE_H_
#include "Entidad.h"
#include <string>
#include "audio/AlSource.h"
#include "audio/AlBuffer.h"

class Personaje:public Entidad{
    public:
    enum class Estado{
       Caminando,
       Corriendo,
       Parado,
       Saltando,
       Cayendo,
       Esquivando,
       Herir,
       Atacando,
       Muerto
    };
   Estado estado;
   virtual void act(float dt);
   void iniciarSalto();
   void detenerSalto();
   void atacar();
   void detener();
   void esquivar();
   virtual void colisiona(Colision c);
   void herir();
   void ejesMover(float x,float y);
   std::string getEstado();
   int vida=3;
   AlBuffer snatacar{"res/atacar.wav"};
   AlBuffer snherido{"res/herido.wav"};
   AlSource source;
   bool lateral=false;

};
#endif

