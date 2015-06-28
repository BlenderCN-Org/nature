#include "Juego.h"
#include <chrono>
#include <iostream>
#include "mapa/Generador.h"
#include "includeglm.h"
#include "vista/RepMap.h"
#include "vista/RepSer.h"
#include "vista/RepPer.h"
#include "entidades/Ser.h"
#include <queue>
#include <map>
//#include <thread>
#include "fisica/Colisionador.h"
#include "config.h"
#include "managers/Managers.h"
#include "vista/RepFactory.h"
using namespace std;
using namespace glm;
void imprimirMatriz(mat4 mat){
    for(int y=0;y<4;y++){
        cout<<"(";
        for(int x=0;x<4;x++){
            cout<<(x>0?",":"")<<mat[x][y];
        }
        cout<<")"<<endl;
    }
}
Juego::Juego():
mapa{20,20,1},
camara(45.0f, 1024.0f / 680.0f, 1.0f, 2000.f)
{
    cout<<"creando Sonido"<<endl;
    ent.reserve(10);

//     buffer=move(OggBuffer::cargar(Path::res("Bomb.ogg")));
     listener.setPos(vec3(0,0,0));
     listener.setVel(vec3(0,0,0));
     listener.setOri(vec3(0,0,-1));
     source.setPos(vec3(1,0,0));
     source.setGain(1.0);
     source.setPitch(1.0);
     source.setLoop(true);
     source.setVel(vec3(0,0,0));
     luz.pos=vec3(-0.2,-1,0.6);
     unique_ptr<Personaje> repCubico=unique_ptr<Personaje>(new Personaje(Esqueleto("armas/espadagrande/esqueleto.mesh.esq")));
     repCubico->pos=vec3(100,10,60);
     repCubico->rep=RepFactory::being(repCubico->type);

     unique_ptr<Ser> repSer= unique_ptr<Ser>(new Ser(Esqueleto("turos.mesh.esq")));
     repSer->rep=RepFactory::being(repSer->type);
     repSer->pos=vec3(100,15,55);
 
     ctrCam=unique_ptr<ControlCamara>(new CamSegPaj(vec3(90,0,-22),repCubico.get(),repSer.get(),&camara));
     ent.push_back(move(repCubico));
     ent.push_back(move(repSer));
     ((Monstruo*)ent[1].get())->p=(Personaje*) repCubico.get();
     generarMapa();
     camara.desplazar(vec3(10,-20,40));
     camara.rotar(vec3(90,0,0));
     vec3 oc=camara.getOrientacion();
        
     cout<<"Or.ent->cion ("<<oc.x<<","<<oc.y<<","<<oc.z<<")"<<endl;
     cout<<"Memoria:"<<mapa.getTamX()*mapa.getTamY()*mapa.getTamZ()*sizeof(Voxel)/1024<<"KB"<<endl;
}



Juego::~Juego()
{
}

void Juego::ejes(float x,float z){
    if(primerEje){
        primerEje=false;
    }else{
       ctrCam->ejes(-x,z);
    }
};


void Juego::movimiento(float x,float y,float z){
     //camara.desplazar(vec3(x*t.delta(),y*t.delta(),z*t.delta()));
         vec3 v=vec3(x,y,0);
         Personaje* p=(Personaje*) ent[0].get();
         vec3 vmov=camara.leftXY()*-x+camara.forwardXY()*y;
         p->ejesMover(-vmov.y,vmov.x);
};
void Juego::presionaSalto(){
     Personaje* p=(Personaje*) ent[0].get();
     p->iniciarSalto();
}; 
void Juego::atacar(){
     Personaje* p=(Personaje*) ent[0].get();
        p->atacar();
     
}; 
void Juego::esquivar(){
     Personaje* p=(Personaje*) ent[0].get();
     p->esquivar();
}; 

void Juego::sueltaSalto(){
     Personaje* p=(Personaje*) ent[0].get();
     p->detenerSalto();
}; 
void Juego::ejeMovimiento(float x,float y){
}; 


void Juego::generarMapa()
{
     queue<Bloque> bloques;
     int total=0;
     int actual=0;
     for(Bloque b:mapa.bloques){
          bloques.push(b);
     }
     total=bloques.size();
     Generador::generar(&mapa,&bloques);
     MeshDatos md("mapa");
    // Generador::generarVoxelizar(&mapa,md,1.0);
     mapa.detectarBordes();
     repMapa.reset(new RepMap(mapa));
     repMapa->sha=unique_ptr<Shader>(new Shader(Path::shader("basico.vert"),Path::shader("basico.frag")));
   //  repMapa->meshUnica=unique_ptr<Mesh>(new Mesh(md));
}
void Juego::loop()
{
   t.actualizar();
   tacumf+=t.delta();
   while(tacumf>0.02f){
       for (auto &e:ent){
           fisica.aplicar(*e,mapa,0.02f);
           e->actf(0.02f);
       }
       tacumf-=0.02f;
   }
   ctrCam->act(t.delta());
   luz.pos=vec3(rotate(mat4(1.0f),radians(-0.11f*t.delta()),vec3(1,0,0))*vec4(luz.pos,0));
   if(luz.pos.z<0) luz.pos=vec3(-0.2,-1,0);
   render();
   
}

void Juego::render(){
   glViewport(0,0,1024,680); 
   for (auto& e:ent){
          e->act(t.delta());
          if(e->rep!=nullptr){
             e->rep->dibujar(e.get(),camara,luz);
//             cout<<"dibujando"<<endl;
          }
//          r->dibujar(camara,luz);
   }
   repMapa->dibujar(camara,luz);
}




