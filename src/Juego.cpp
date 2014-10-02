#include "Juego.h"
#include <chrono>
#include <iostream>
#include "mapa/Generador.h"
#include "includeglm.h"
#include "RepresentacionMapa.h"
#include <queue>
#include <thread>

using namespace std;
Juego::Juego():
mapa{5,5,4},
camara(45.0f, (float)600.0 / (float)600.0, 0.1f, 1200.f)
{

     Shader* s=new Shader(GestorRutas::getRutaShader("basico.vert"),GestorRutas::getRutaShader("basico.frag"));
     shaders.push_back( unique_ptr<Shader>(s));
     rep.mesh= unique_ptr<Mesh>(new Mesh("capibara"));
     rep.entidad.pos=glm::vec3(0.0,0.0,0.0);
     generarMapa();
     mapa.detectarBordes();
     camara.desplazar(glm::vec3(0,-20,0));

     camara.rotar(glm::vec3(90,0,0));
     repMapa.reset(new RepresentacionMapa(mapa));

}



Juego::~Juego()
{
     //dtor
     //
}

void Juego::ejes(float x,float z){
   camara.rotar(glm::vec3(x*t.delta(),0,z*t.delta()));
};
void Juego::teclaMovimiento(float x,float y,float z){
     camara.desplazar(glm::vec3(x*t.delta(),y*t.delta(),z*t.delta()));
};


void Juego::generarMapa()
{
     thread hilos[4];
     cout<<"sizeof(Voxel)="<<sizeof(Voxel)<<"; Tamano Mapa="<<30*30*4*32*32*32*sizeof(Voxel)/1000/1000<<endl;
     unique_ptr<mutex>  mt{new mutex()};
     queue<Bloque> bloques;
     int total=0;
     int actual=0;
     

     for(Bloque b:mapa.bloques){
          bloques.push(b);
     }
     total=bloques.size();


     for(int i=0;i<4;++i){

          hilos[i]=std::thread(&Generador::generar,&mapa,&bloques,mt.get());
     }
     bool vacia=false;
     do{
          mt->lock();
          vacia=bloques.empty();
            actual=total-bloques.size();
          mt->unlock();

         // cout<<"Generados "<<actual<<" de "<<total<<endl;
     }while(!vacia);


     for(int i=0;i<4;++i){
          hilos[i].join();
     }
}
void Juego::loop()
{
   t.actualizar();
   shaders[0]->matProy=camara.getMatProy();
   shaders[0]->matVista=camara.getMatVista();
   
   rep.entidad.rotar(glm::vec3(0,0,20.0*t.delta()));
   #fisica.aplicar(rep.entidad,t.delta());
   rep.mesh.get()->dibujar(shaders[0].get(),rep.entidad.getMatModelo());
   for(unique_ptr<MeshBloque>& mesh:repMapa->meshes){
     mesh->dibujar(shaders[0].get(),glm::mat4(1.0));
   }
  //cout<<"loop"<<endl;




}
