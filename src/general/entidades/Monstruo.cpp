#include "Monstruo.h"
#include "includeglm.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <random>
#include <functional>
#include <chrono>
using namespace std;
using namespace glm;

void Monstruo::act(float dt){
    if(p!=NULL){
        float d=glm::distance(p->pos,this->pos);
        float dh=glm::distance(vec2(p->pos.x,p->pos.y),vec2(this->pos.x,this->pos.y));
        vec3 dir=normalize(p->pos-this->pos);
        vec3 dirh=normalize(vec3(dir.x,dir.y,0));
        switch(estado){
            case Estado::Caido:
                tiempoCaido+=dt;
                if(tiempoCaido>3){
                    estado=Estado::Detenido;
                }
            break; 
            case Estado::Herido:
                tiempoHerido+=dt;
                if(tiempoHerido>2){
                    estado=Estado::Detenido;
                }else{
                   this->vel=-dirh*22.0f;
                   this->direccion=glm::rotation(vec3(0,-1,0),-dirh);
                }
            break;
 
            case Estado::Detenido:
                if(tiempoDetenido>2){
                    this->vel=dirh*5.0f;
                    estado=Estado::Caminando;
                    this->direccion=glm::rotation(vec3(0,-1,0),dirh);
                    break;
                }
            case Estado::Caminando:
                   if(d<7){
                      int ataque=rand()%2;
                      if(lateral) ataque=0;
                     if(ataque==1){
                          estado=Estado::AtaqueBomba;
                          zBomba=this->pos.z;
                          this->vel=dirh*8.0f+vec3(0,0,25);
                          this->direccion=glm::rotation(vec3(0,-1,0),dirh);
                     }else{ 
                          estado=Estado::AtaqueGirar;
                          this->vel=dirh*45.0f;
                          this->direccion=glm::rotation(vec3(0,-1,0),dirh);

                     }
                     source.play(sngrunir1);
                }else{
                    if(lateral)
                        this->vel=dirh*22.0f;
                    else
                        this->vel=dirh*30.0f;
                    estado=Estado::Caminando;
                    this->direccion=glm::rotation(vec3(0,-1,0),dirh);
                }
                   if(lateral&&pos.x>460){
                      this->vel=vec3(0,0,-10);
                   }
              break;
            case Estado::AtaqueBomba:

                 this->vel=dirh*8.0f+vec3(vel.x,vel.y,vel.z);
                 if(dh<2||pos.z>zBomba+10){
                     vel.z=-30;
                     vel.x=0;
                     vel.y=0;
                 }
            break;
            case Estado::Encerrado:
            break;
            case Estado::Muerto:
            break;
        }
    }
    
}
void Monstruo::detener(){
    if(estado!=Estado::Muerto){
        estado=Estado::Detenido;
        tiempoCaido=0.0f;
        this->vel=vec3(0,0,0);
    }

}
void Monstruo::liberar(){
    estado=Estado::Detenido;
}
void Monstruo::colisiona(Colision c){
    if(estado==Estado::AtaqueBomba){
        if(this->vel.z==0){
            estado=Estado::Caido;
            tiempoCaido=0.0f;
        }
        this->vel=vec3(0,0,vel.z);
        if(this->pos.z<8){
            estado=Estado::Muerto;
        }
    }
}
void Monstruo::herir(){
   if(estado!=Estado::Herido&&estado!=Estado::Muerto){
       vida--;
       estado=Estado::Herido;
       source.play(snherido);
       tiempoHerido=0.0f;
       if(vida<=0){
          estado=Estado::Muerto;
       }
   }
}
