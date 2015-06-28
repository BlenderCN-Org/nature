#ifndef _PERSONAJE_H_
#define _PERSONAJE_H_
#include "audio/AlSource.h"
#include "audio/AlBuffer.h"
#include "entidades/EntidadEsq.h"
#include <string>
#include "esqueleto/Esqueleto.h"
#include "esqueleto/Animador.h"
#include "Ser.h"

class Personaje:public Ser{
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
       Muerto,
    };
    std::string eststr(Estado e){
       std::string s="indefinido";
       switch(e){
           case Estado::Caminando:s=envainada?"caminar":"caminarArma";break;
           case Estado::Corriendo:s=envainada?"correr":"correrArma";break;
           case Estado::Parado:   s=envainada?"parado":"paradoArma";break;
           case Estado::Saltando: s=envainada?"saltar":"saltarArma";break;
           case Estado::Cayendo:  s=envainada?"caer":"caerArma";break;
           case Estado::Esquivando:s=envainada?"esquivar":"esquivarArma";break;
           case Estado::Herir:    s=envainada?"herir":"herirArma";break;
           case Estado::Atacando: s="ataque"+std::string(2-cadenaAtaque%2,tipoAtaque==1?'2':'2');break;
           case Estado::Muerto:   s=envainada?"muerto":"muertoArma";break;
       }
       return s;

   }
   Estado estado;
   int tipoAtaque=1;
   int cadenaAtaque=1;
   bool envainada=false;

   void camEst(Estado e);
   Personaje(Esqueleto e);
   virtual void act(float dt);
   virtual void actf(float dt);
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

