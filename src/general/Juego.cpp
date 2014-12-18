#include "Juego.h"
#include <chrono>
#include <iostream>
#include "mapa/Generador.h"
#include "includeglm.h"
#include "RepresentacionMapa.h"
#include <queue>
#include <map>
//#include <thread>
#include "fisica/Colisionador.h"
#include "config.h"

using namespace std;
void imprimirMatriz(glm::mat4 mat){
    for(int y=0;y<4;y++){
        cout<<"(";
        for(int x=0;x<4;x++){
            cout<<(x>0?",":"")<<mat[y][x];
        }
        cout<<")"<<endl;
    }
}
Juego::Juego():
mapa{1,1,1},
camara(45.0f, 640.0f / 480.0f, 1.0f, 100.f)
{

     cout<<"Creando juego"<<endl;
     cout<<"Cargando shader "<<endl;

     Shader* s=new Shader(GestorRutas::getRutaShader("basico.vert"),GestorRutas::getRutaShader("basico.frag"));
     shaders.push_back( unique_ptr<Shader>(s));

     s=new Shader(GestorRutas::getRutaShader("animado.vert"),GestorRutas::getRutaShader("basico.frag"),map<string,string>{{"%nhuesos%","6"}});
     shaders.push_back( unique_ptr<Shader>(s));

     s=new Shader(GestorRutas::getRutaShader("animado.vert"),GestorRutas::getRutaShader("basico.frag"),map<string,string>{{"%nhuesos%","6"}});
     shaders.push_back( unique_ptr<Shader>(s));

     //s=new Shader(GestorRutas::getRutaShader("esqueleto.vert"),GestorRutas::getRutaShader("basico.frag"));
     //shaders.push_back( unique_ptr<Shader>(s));

     s=new Shader(GestorRutas::getRutaShader("borde.vert"),GestorRutas::getRutaShader("basico.frag"));
     shaders.push_back( unique_ptr<Shader>(s));


     s=new Shader(GestorRutas::getRutaShader("bordeanimado.vert"),GestorRutas::getRutaShader("basico.frag"),map<string,string>{{"%nhuesos%","6"}});
     shaders.push_back( unique_ptr<Shader>(s));

     s=new Shader(GestorRutas::getRutaShader("bordeanimado.vert"),GestorRutas::getRutaShader("basico.frag"),map<string,string>{{"%nhuesos%","6"}});
     shaders.push_back( unique_ptr<Shader>(s));
     cout<<"Cargando mesh capibara "<<endl;
     //rep.push_back(move(RepresentacionEntidad()));
     cout<<"**rep"<<rep.size()<<endl;
//     esq=unique_ptr<Esqueleto>(new Esqueleto("esqueleto.mesh.esq"));


//     cout<<"nhuesos"<<esq->huesos.size()<<endl;
     cubo=unique_ptr<Mesh>(new Mesh("cubo"));
     rep[0].mesh= unique_ptr<Mesh>(new Mesh("capibara"));
     rep[0].entidad.nombre="mono";
     rep[0].entidad.pos=glm::vec3(3.0f,3.0f,6.0f);
     rep[0].entidad.vel=glm::vec3(0.0f,0.0f,9.0f);
     rep[0].shader=shaders[0].get();
     rep[0].entidad.rebote=0.2f;
     //rep.push_back(std::move(RepresentacionEntidad()));
     rep[1].mesh= unique_ptr<Mesh>(new Mesh("cubico"));
     rep[1].esq= unique_ptr<Esqueleto>(new Esqueleto("cubico.mesh.esq"));
     rep[1].entidad.pos=glm::vec3(3.0f,12.0f,6.0f);
     rep[1].entidad.rotar(glm::vec3(0,0,90));
     rep[1].entidad.rebote=0.0f;
     rep[1].entidad.vel=glm::vec3(0.0f,0.0f,09.0f);
     rep[1].shader=shaders[1].get();
     rep[1].shaderBorde=shaders[4].get();

     rep[2].mesh= unique_ptr<Mesh>(new Mesh("hoja"));
     rep[2].esq= unique_ptr<Esqueleto>(new Esqueleto("hoja.mesh.esq"));
     rep[2].entidad.pos=glm::vec3(2.0f,6.0f,6.0f);
     rep[2].entidad.rotar(glm::vec3(0,0,90));
     rep[2].entidad.vel=glm::vec3(0.0f,0.0f,09.0f);
     rep[2].shader=shaders[2].get();
     rep[2].shaderBorde=shaders[5].get();

     rep[3].mesh= unique_ptr<Mesh>(new Mesh("isla"));
     rep[3].entidad.nombre="Mapa";
     rep[3].entidad.pos=glm::vec3(0.0f,0.0f,0.0f);
     rep[3].entidad.rotar(glm::vec3(0,0,0));
     rep[3].entidad.vel=glm::vec3(0.0f,0.0f,0.0f);
     rep[3].entidad.gravedad=0.0f;
     rep[3].shader=shaders[1].get();
     rep[3].shaderBorde=shaders[3].get();


     esqMesh=unique_ptr<MeshEsqueleto>(new MeshEsqueleto(*rep[1].esq));
     generarMapa();
     mapa.detectarBordes();
     camara.desplazar(glm::vec3(0,-20,0));
     camara.rotar(glm::vec3(89.5,0,0));
     glm::vec3 oc=camara.getOrientacion();
     cout<<"Orientacion ("<<oc.x<<","<<oc.y<<","<<oc.z<<")"<<endl;
     repMapa.reset(new RepresentacionMapa(mapa));

}



Juego::~Juego()
{
}

void Juego::ejes(float x,float z){
   camara.rotar(glm::vec3(x*0.1*t.delta(),0,z*0.1*t.delta()));
};
void Juego::teclaMovimiento(float x,float y,float z){
     camara.desplazar(glm::vec3(x*t.delta(),y*t.delta(),z*t.delta()));
};


void Juego::generarMapa()
{
//     thread hilos[4];

     DEBUG(/*{{{*/
           cout<<"sizeof(Voxel)="<<sizeof(Voxel)<<"; Tamano Mapa="<<30*30*4*32*32*32*sizeof(Voxel)/1000/1000<<endl;
     )/*}}}*/

 //    unique_ptr<mutex>  mt{new mutex()};
     queue<Bloque> bloques;
     int total=0;
     int actual=0;
     

     for(Bloque b:mapa.bloques){
          bloques.push(b);
     }
     total=bloques.size();
     Generador::generar(&mapa,&bloques);


     /*for(int i=0;i<4;++i){

          hilos[i]=std::thread(&Generador::generar,&mapa,&bloques,mt.get());
     }
     bool vacia=false;
     do{
          mt->lock();
          vacia=bloques.empty();
            actual=total-bloques.size();
          mt->unlock();
*/
          DEBUG(/*{{{*/
                  cout<<"Generados "<<actual<<" de "<<total<<endl;
          )/*}}}*/
  /*   }while(!vacia);
     */


     /*for(int i=0;i<4;++i){
          hilos[i].join();
     }*/
}
void Juego::loop()
{
   t.actualizar();
   if(tanim>2.0f)tanim=0.0f;
   for(auto &s:shaders){
     s->matProy=camara.getMatProy();
     s->matVista=camara.getMatVista();
     s->vecVista=camara.getOrientacion();
   }
   
   tacumf+=t.delta();
   int i=0;
//   cout<<"dtfs:"<<dtf<<endl;
  // cout<<"camara pos;rot: ("<<camara.pos.x<<","<<camara.pos.y<<","<<camara.pos.z<<");";
//   cout<<"("<<camara.rot.x<<","<<camara.rot.y<<","<<camara.rot.z<<");";
   while(tacumf>0.02f){
       for (RepresentacionEntidad &r:rep){
           fisica.aplicar(r.entidad,mapa,0.02f);
       }
       tacumf-=0.02f;
       ++i;
   }
//       cout<<"dtfs:"<<i<<endl;

   for (RepresentacionEntidad &r:rep){
       if(r.esq){
          r.mesh->dibujar(r.shader,r.entidad.getMatModelo(),r.esq->getPose("aa",tanim),r.esq->bindPoses);
          r.mesh->dibujar(r.shaderBorde,r.entidad.getMatModelo(),r.esq->getPose("aa",tanim),r.esq->bindPoses,false);
       }else{
           r.mesh->dibujar(r.shader,r.entidad.getMatModelo());
           r.mesh->dibujar(shaders[3].get(),r.entidad.getMatModelo(),false);

       }
   }
   tanim+=t.delta()*1.0;
   //for(unique_ptr<MeshBloque>& mesh:repMapa->meshes){
   //  mesh->dibujar(shaders[0].get(),glm::mat4(1.0f));
   //}
}
