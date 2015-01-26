#include "Personaje.h"

using namespace std;
using namespace glm;
void Personaje::act(float dt){
    if(estado!=Estado::Muerto){
        if(estado!=Estado::Atacando&&estado!=Estado::Herir){
            if(vel.z<0){
                estado=Estado::Cayendo;
            }else if(vel.z==0&&vel.y==0&&vel.x==0&&estado!=Estado::Atacando){
                estado=Estado::Parado;
            }else if(vel.z==0&&(vel.y!=0||vel.x!=0)&&estado!=Estado::Atacando){
                estado=Estado::Corriendo;
            }
        }
    }
    
    
};
std::string Personaje::getEstado(){
    string e="Desconocido";
        switch(estado){
           case Personaje::Estado::Caminando:
               e="Caminando";
           break;
           case Personaje::Estado::Saltando:
               e="Saltando";
           break;
           case Personaje::Estado::Cayendo:

               e="Cayendo";
           break;
           case Personaje::Estado::Corriendo:

               e="correr";
           break;
           case Personaje::Estado::Parado:
               e="parado";
           break;
           case Personaje::Estado::Atacando:
               e="Atacando";
           break;
           case Personaje::Estado::Esquivando:
               e="Esquivando";


       }
return e; 
}
void Personaje::iniciarSalto(){
    if(estado!=Estado::Muerto){
       if(estado!=Estado::Cayendo&&estado!=Estado::Saltando){
           if(pos.x>447)
              vel=vec3(vel.x,vel.y,10);
           else
              vel=vec3(vel.x,vel.y,5);
           this->estado=Estado::Saltando;
       }
    }
};
void Personaje::colisiona(Colision c){
    if(estado!=Estado::Muerto){
        if(estado==Estado::Herir){
           cout<<"Detener PErsonaje"<<endl;
           detener();    
        }
        if(this->pos.z<8){
            estado=Estado::Muerto;
        }
 
    }else{
    }

};
void Personaje::detenerSalto(){
    if(estado!=Estado::Muerto){
       vel=vec3(vel.x,vel.y,vel.z>0?0:vel.z);
       estado=Estado::Cayendo;
    }
}
void Personaje::atacar(){
    if(estado!=Estado::Muerto&&estado!=Estado::Herir){
  // if(estado==Estado::Caminando||
  //    estado==Estado::Corriendo||
 //     estado==Estado::Parado){
//           vel=vec3(vel.x,vel.y,vel.z);
       if(estado!=Estado::Atacando){
           source.play(snatacar);
       }
           estado=Estado::Atacando;
  // }
   }
}
void Personaje::detener(){

    if(estado!=Estado::Muerto){
  // if(estado==Estado::Caminando||
  //    estado==Estado::Corriendo||
 //     estado==Estado::Parado){
           vel=vec3(0,0,0);
           estado=Estado::Parado;
  // }
   }
}

void Personaje::esquivar(){
    if(estado!=Estado::Muerto){
       if(estado==Estado::Caminando||
          estado==Estado::Corriendo||
          estado==Estado::Parado){
    //           vel=vec3(vel.x,vel.y,vel.z);
               estado=Estado::Esquivando;
       }
    }
}
void Personaje::herir(){
    if(estado!=Estado::Muerto){
      if(estado!=Estado::Herir){
          if(lateral)
              vida=0;
          else
              vida--;
        if(vida<=0){
          vel=vec3(0,0,10);
          estado=Estado::Muerto;
        }else{
          vel=vec3(10,3,10);
          estado=Estado::Herir;
        }
      }
      source.play(snherido);
    }
}

void Personaje::ejesMover(float x, float y){
    if(estado!=Estado::Muerto){
        if(x!=0.0f||y!=0){
          if(estado!=Estado::Saltando&&estado!=Estado::Cayendo&&estado!=Estado::Atacando&&estado!=Estado::Herir){
              direccion=quat(vec3(0,0,orientedAngle(normalize(vec3(x,y,0)),vec3(0,-1,0),vec3(0,0,-1))));
              vel.x=x*22;
              vel.y=y*22;
              estado=Estado::Corriendo;
          }else{
              vel.x=x*22;
              vel.y=y*22;
          }
          
        }else{
          if(estado!=Estado::Saltando&&estado!=Estado::Cayendo&&estado!=Estado::Atacando&&estado!=Estado::Herir){
              vel.x=0;
              vel.y=0;
              estado=Estado::Parado;
          }else{
              vel.x*=0.3f;
              vel.y*=0.3f;
          }
        }
    }
}
