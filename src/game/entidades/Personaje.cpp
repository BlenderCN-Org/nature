#include "Personaje.h"

using namespace std;
using namespace glm;
Personaje::Personaje(Esqueleto e):
    Ser(move(e),BeingType::Human)
{
    gravedad=1.0f;
    rebote=0.0f;
}
void Personaje::camEst(Estado e){
    estado=e;
    bool l=false;
    bool r=false;
    switch(e){
           case Estado::Caminando:  l=true ,r=false;break;
           case Estado::Corriendo:  l=true ,r=false;break;
           case Estado::Parado:     l=true ,r=false;break;
           case Estado::Saltando:   l=false,r=false;break;
           case Estado::Cayendo:    l=false,r=false;break;
           case Estado::Esquivando: l=false,r=false;break;
           case Estado::Herir:      l=false,r=false;break;
           case Estado::Atacando:   l=false,r=false;break;
           case Estado::Muerto:     l=false,r=true;break;
    }
    ani.animar(eststr(estado),l,r);
}
void Personaje::act(float dt){
    ani.act(dt);
    if(estado!=Estado::Muerto){
        if(estado!=Estado::Atacando&&estado!=Estado::Herir){
            if(vel.z<0){
                camEst(Estado::Cayendo);
            }else if(vel.z==0&&vel.y==0&&vel.x==0&&estado!=Estado::Atacando){
                camEst(Estado::Parado);
            }else if(vel.z==0&&(vel.y!=0||vel.x!=0)&&estado!=Estado::Atacando){
                camEst(Estado::Corriendo);
            }
        }
    }
    if(estado==Estado::Atacando&&ani.actual()==ani.id(eststr(estado))&&ani.terminado()){
       detener(); 
    }
};
void Personaje::actf(float dt){

}
std::string Personaje::getEstado(){
    return eststr(estado);
}
void Personaje::iniciarSalto(){
    if(estado!=Estado::Muerto){
       if(estado!=Estado::Cayendo&&estado!=Estado::Saltando){
           vel=vec3(vel.x,vel.y,3);
           camEst(Estado::Saltando);
       }
    }
};
void Personaje::colisiona(Colision c){
    if(estado!=Estado::Muerto){
        if(estado==Estado::Herir){
           detener();    
        }
        if(this->pos.z<8){
            camEst(Estado::Muerto);
        }
 
    }else{
    }

};
void Personaje::detenerSalto(){
    if(estado!=Estado::Muerto){
       vel=vec3(vel.x,vel.y,vel.z>0?0:vel.z);
       camEst(Estado::Cayendo);
    }
}
void Personaje::atacar(){
    if(estado!=Estado::Muerto&&estado!=Estado::Herir){
  // if(estado==Estado::Caminando||
  //    estado==Estado::Corriendo||
 //     estado==Estado::Parado){
//           vel=vec3(vel.x,vel.y,vel.z);
       if(estado!=Estado::Atacando){
           cadenaAtaque=1;
           source.play(snatacar);
       }else{
           cadenaAtaque++;
           source.play(snatacar);
       }
//       vel=vec3(0,0,0);
       camEst(Estado::Atacando);
  // }
   }
}
void Personaje::detener(){

    if(estado!=Estado::Muerto){
  // if(estado==Estado::Caminando||
  //    estado==Estado::Corriendo||
 //     estado==Estado::Parado){
           vel=vec3(0,0,0);
           camEst(Estado::Parado);
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
              vel.x=x*5.5f;
              vel.y=y*5.5f;
              camEst(Estado::Corriendo);
          }else{
/*              vel.x=x*5.5f;
              vel.y=y*5.5f;*/
          }
        }else{
          if(estado!=Estado::Saltando&&estado!=Estado::Cayendo&&estado!=Estado::Atacando&&estado!=Estado::Herir){
              detener();
          }else{
              vel.x*=0.3f;
              vel.y*=0.3f;
          }
        }
    }
}
