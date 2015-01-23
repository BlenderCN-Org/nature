#include "Juego.h"
#include <chrono>
#include <iostream>
#include "mapa/Generador.h"
#include "includeglm.h"
#include "vista/RepMap.h"
#include <queue>
#include <map>
//#include <thread>
#include "fisica/Colisionador.h"
#include "config.h"

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
mapa{5,5,4},
camara(45.0f, 640.0f / 480.0f, 1.0f, 2000.f),
shadowMap(2048,2048) 
{

     buffer=OggBuffer::cargar(Path::res("Bomb.ogg"));
     listener.setPos(vec3(0,0,0));
     listener.setVel(vec3(0,0,0));
     source.setPos(vec3(0,0,0));
     source.setGain(1.0);
     source.play(buffer);
     luz.pos=vec3(-0.2,-1,0.6);
     
     RepEnt repCubico;
     repCubico.mesh=unique_ptr<Mesh>(new Mesh(MeshDatos("cubico")));
     repCubico.ent=unique_ptr<Entidad>(new Personaje());
     repCubico.esq=unique_ptr<Esqueleto>(new Esqueleto("cubico.mesh.esq"));
     repCubico.ani=unique_ptr<Animador>(new Animador(*repCubico.esq));
     repCubico.ani->animar("correr",true);
     repCubico.ent->gravedad=2.0f;
     repCubico.ent->pos=vec3(20,20,20);
     repCubico.ent->rebote=0.0f;
     repCubico.ent->vel=vec3(0.0f,0.0f,09.0f);
     repCubico.ent->ace=vec3(0.0f,0.0f,0.0f);
     repCubico.sha=unique_ptr<Shader>(new Shader(Path::shader("animado.vert"),Path::shader("basico.frag"),map<string,string>{{"%nhuesos%","6"}}));

     RepEnt repEjes;
     repEjes.mesh=unique_ptr<Mesh>(new Mesh(MeshDatos("cubo")));
     //repEjes.mesh=unique_ptr<Mesh>(new Mesh(MeshDatos::plano(10,10)));
     repEjes.ent=unique_ptr<Entidad>(new Entidad());
     repEjes.ent->gravedad=1.0f;
     repEjes.ent->rebote=0.0f;
     repEjes.ent->pos=vec3(20,20,40);
     repEjes.ent->vel=vec3(0.0f,0.0f,09.0f);
     repEjes.ent->ace=vec3(0.0f,0.0f,0.0f);
     repEjes.sha=unique_ptr<Shader>(new Shader(Path::shader("basico.vert"),Path::shader("basico.frag")));

     RepEnt repDragon;
     repDragon.mesh=unique_ptr<Mesh>(new Mesh(MeshDatos("dragon")));
     repDragon.ent=unique_ptr<Entidad>(new Entidad());
     repDragon.ent->gravedad=1.0f;
     repDragon.ent->rebote=0.0f;
     repDragon.ent->pos=vec3(50,20,40);
     repDragon.ent->vel=vec3(0.0f,0.0f,09.0f);
     repDragon.ent->ace=vec3(0.0f,0.0f,0.0f);
     repDragon.sha=unique_ptr<Shader>(new Shader(Path::shader("basico.vert"),Path::shader("basico.frag")));
     
     ctrCam=unique_ptr<ControlCamara>(new CamSegPaj(vec3(32,0,-90),repCubico.ent.get(),&camara));
     rep.push_back(move(repCubico));
     rep.push_back(move(repEjes));
     rep.push_back(move(repDragon));

     generarMapa();

     camara.desplazar(vec3(10,-20,40));
     camara.rotar(vec3(89.5,0,0));
     vec3 oc=camara.getOrientacion();
     cout<<"Or.ent->cion ("<<oc.x<<","<<oc.y<<","<<oc.z<<")"<<endl;
     cout<<"Memoria:"<<mapa.getTamX()*mapa.getTamY()*mapa.getTamZ()*sizeof(Voxel)/1024<<"KB"<<endl;

}



Juego::~Juego()
{
}

void Juego::ejes(float x,float z){
    ctrCam->ejes(x,z);
};
void Juego::movimiento(float x,float y,float z){
     //camara.desplazar(vec3(x*t.delta(),y*t.delta(),z*t.delta()));
     vec3 v=vec3(x,y,0);


     Personaje* p=(Personaje*) rep[0].ent.get();
     p->ejesMover(x,y);
     /*if(x==0&&y==0){
       if(rep[0].ani->id("parado")!=rep[0].ani->actual())
          rep[0].ani->animar("parado",true);
     }else{
       if(rep[0].ani->id("correr")!=rep[0].ani->actual())
          rep[0].ani->animar("correr",true);
     }*/
};
void Juego::presionaSalto(){
     Personaje* p=(Personaje*) rep[0].ent.get();
     p->iniciarSalto();
}; 

void Juego::sueltaSalto(){
     Personaje* p=(Personaje*) rep[0].ent.get();
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
     Generador::generarVoxelizar(&mapa,md,1.0);
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
       for (RepEnt &r:rep){
           fisica.aplicar(*r.ent,mapa,0.02f);
           r.ent->act(0.02f);
           if(r.ent->pos.z<0){
                r.ent->pos=vec3(20,20,40);
           }
       }
       tacumf-=0.02f;
   }

   ctrCam->act(t.delta());
   luz.pos=vec3(rotate(mat4(1.0f),radians(-0.11f*t.delta()),vec3(1,0,0))*vec4(luz.pos,0));
   if(luz.pos.z<0) luz.pos=vec3(-0.2,-1,0);
   //cout<<"REnder"<<endl;
   render();
   
}

void Juego::render(){
   glViewport(0,0,1024,680); 
   for (RepEnt &r:rep){
          r.act(t.delta());
          r.dibujar(camara,luz);
   }
   repMapa->dibujar(camara,luz);
}
