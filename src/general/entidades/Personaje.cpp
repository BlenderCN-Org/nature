#include "Personaje.h"

using namespace std;
using namespace glm;
void Personaje::act(float dt){
    if(vel.z<0){
        estado=Estado::Cayendo;
    }else if(vel.z==0&&vel.y==0&&vel.x==0){
        estado=Estado::Parado;
    }else if(vel.z==0&&(vel.y!=0||vel.x!=0)){
        estado=Estado::Corriendo;
    }
    
};
void Personaje::iniciarSalto(){
   if(estado!=Estado::Cayendo&&estado!=Estado::Saltando){
       vel=vec3(vel.x,vel.y,10);
       this->estado=Estado::Saltando;
   }
};
void Personaje::detenerSalto(){
   vel=vec3(vel.x,vel.y,vel.z>0?0:vel.z);
   estado=Estado::Cayendo;
}
void Personaje::ejesMover(float x, float y){
    if(x!=0.0f||y!=0){
//      if(estado!=Estado::Saltando&&estado!=Estado::Cayendo){
          direccion=quat(vec3(0,0,orientedAngle(normalize(vec3(x,y,0)),vec3(0,-1,0),vec3(0,0,-1))));
          vel.x=x*22;
          vel.y=y*22;
          estado=Estado::Corriendo;
  //    }
      
    }else{

      if(estado!=Estado::Saltando&&estado!=Estado::Cayendo){
          vel.x=0;
          vel.y=0;
          estado=Estado::Parado;
      }else{
          vel.x*=0.3f;
          vel.y*=0.3f;
      }
    }
}
