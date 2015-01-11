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
mapa{5,3,3},
camara(45.0f, 640.0f / 480.0f, 1.0f, 600.f),
shadowMap(2048,2048) 
{

     cout<<"Creando juego"<<endl;
     cout<<"Cargando shader "<<endl;
     luz=vec3(0.1,-1,0.6);
     Shader* s=new Shader(GestorRutas::getRutaShader("basico.vert"),GestorRutas::getRutaShader("basico.frag"));
     shaders.push_back( unique_ptr<Shader>(s));

     s=new Shader(GestorRutas::getRutaShader("basico.vert"),GestorRutas::getRutaShader("textura.frag"));
     s->usarTex=true;
     Imagen img(GestorRutas::getRuta("islablender.png"));
     s->tex= new Textura(img);
     shaders.push_back( unique_ptr<Shader>(s));

     cout<<"Borde "<<endl;
     s=new Shader(GestorRutas::getRutaShader("borde.vert"),GestorRutas::getRutaShader("basico.frag"));
     shaders.push_back( unique_ptr<Shader>(s));

     cout<<"Animado 1"<<endl;
     s=new Shader(GestorRutas::getRutaShader("animado.vert"),GestorRutas::getRutaShader("basico.frag"),map<string,string>{{"%nhuesos%","6"}});
     shaders.push_back( unique_ptr<Shader>(s));

     cout<<"Animado Borde 1"<<endl;
     s=new Shader(GestorRutas::getRutaShader("bordeanimado.vert"),GestorRutas::getRutaShader("basico.frag"),map<string,string>{{"%nhuesos%","6"}});
     shaders.push_back( unique_ptr<Shader>(s));

     cout<<"Sombra"<<endl;
     s=new Shader(GestorRutas::getRutaShader("sombra.vert"),GestorRutas::getRutaShader("sombra.frag"));
     shaders.push_back( unique_ptr<Shader>(s));

     cout<<"Sombra Animado"<<endl;
     s=new Shader(GestorRutas::getRutaShader("sombraanimado.vert"),GestorRutas::getRutaShader("sombra.frag"),map<string,string>{{"%nhuesos%","6"}});
     shaders.push_back( unique_ptr<Shader>(s));

     RepresentacionEntidad repCubico;
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
     repCubico.shader=shaders[3].get();
     repCubico.shaderBorde=shaders[4].get();
     repCubico.shaderSombra=shaders[6].get();

     RepresentacionEntidad repEjes;
     repEjes.mesh=unique_ptr<Mesh>(new Mesh(MeshDatos("capibara")));
     //repEjes.mesh=unique_ptr<Mesh>(new Mesh(MeshDatos::plano(10,10)));
     repEjes.ent=unique_ptr<Entidad>(new Entidad());
     repEjes.ent->gravedad=1.0f;
     repEjes.ent->rebote=0.0f;
     repEjes.ent->pos=vec3(20,20,40);
     repEjes.ent->vel=vec3(0.0f,0.0f,09.0f);
     repEjes.ent->ace=vec3(0.0f,0.0f,0.0f);
     repEjes.shader=shaders[0].get();
     repEjes.shaderBorde=shaders[2].get();
     repEjes.shaderSombra=shaders[5].get();
     
     ctrCam=unique_ptr<ControlCamara>(new CamSegPaj(vec3(32,0,-90),repCubico.ent.get(),&camara));
     rep.push_back(move(repCubico));
     rep.push_back(move(repEjes));

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
//Generador::generar(&mapa,&bloques);
     MeshDatos md("mapah");
     Generador::generarVoxelizar(&mapa,md,1.0);
     mapa.detectarBordes();
     repMapa.reset(new RepresentacionMapa(mapa));
     repMapa->meshUnica=unique_ptr<Mesh>(new Mesh(md));

     /*for(int i=0;i<4;++i){

          hilos[i]=thread(&Generador::generar,&mapa,&bloques,mt.get());
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
   tacumf+=t.delta();
   while(tacumf>0.02f){
       for (RepresentacionEntidad &r:rep){
           fisica.aplicar(*r.ent,mapa,0.02f);
           r.ent->act(0.02f);
           if(r.ent->pos.z<0){
                r.ent->pos=vec3(20,20,40);
           }
       }
       tacumf-=0.02f;
   }

   ctrCam->act(t.delta());
   for(auto &s:shaders){
     s->matProy=camara.getMatProy();
     s->matVista=camara.getMatVista();
     //vec3 cp=camara.pos;
     //vec3 centro=vec3(32*5/2,32*3/2,32*3/2);
     luz=vec3(rotate(mat4(1.0f),radians(-0.11f*t.delta()),vec3(1,0,0))*vec4(luz,0));
     if(luz.z<0) luz=vec3(-0.2,-1,0);
     s->luz=luz;
   //  cout<<"***"<<endl;
 //    imprimirMatriz(s->matVista);
//     s->matVista=rotate(mat4(1.0f),radians(-180.0f),vec3(1,0,0));
     s->vecVista=camara.getOrientacion();
   }
//   cout<<"Renderizar ShadowMap"<<endl;
   shadowMap.bind(); 
   vec3 centro=vec3(mapa.getTamX()/2,mapa.getTamY()/2,mapa.getTamZ()/2);
   mat4 matLuz;
   glm::mat4 biasMatrix(
0.5, 0.0, 0.0, 0.0,
0.0, 0.5, 0.0, 0.0,
0.0, 0.0, 0.5, 0.0,
0.5, 0.5, 0.5, 1.0
);
   mat4 matPSha=glm::ortho<float>(-mapa.getTamX()/2,mapa.getTamX()/2,-mapa.getTamY()/2,mapa.getTamY()/2,-mapa.getTamZ()/2,mapa.getTamZ()/2);
   mat4 matVSha=glm::lookAt(centro+luz, centro, glm::vec3(0,1,0));
   matLuz=biasMatrix*matPSha*matVSha;
   glViewport(0,0,2048,2048);
   for (RepresentacionEntidad &r:rep){
       r.shaderSombra->shadowMap=nullptr;
       r.shaderSombra->matProy=matPSha;
       r.shaderSombra->matVista=matVSha;
       if(r.esq){
         r.mesh->dibujar(r.shaderSombra,r.ent->getMatModelo(),r.ani->getPose(),r.esq->bindPoses,true);
       }else{
         r.mesh->dibujar(r.shaderSombra,r.ent->getMatModelo(),true);
       }
   }
   if(repMapa->meshUnica){
       repMapa->meshUnica->dibujar(shaders[5].get(),mat4(1.0f));
   }else for(unique_ptr<MeshBloque>& mesh:repMapa->meshes){
       mesh->dibujar(shaders[5].get(),mat4(1.0f));
   }
   shadowMap.unbind();
   glViewport(0,0,1024,680);   
//   shaders[1]->tex=&shadowMap.tcolor;

//   cout<<"Renderizar Escena"<<endl;
   for (RepresentacionEntidad &r:rep){
           r.shader->matLuz=matLuz;
           r.shader->shadowMap=&shadowMap.tdepth;
      if(r.esq){
           Personaje* p= (Personaje*) r.ent.get();
           switch(p->estado){
               case Personaje::Estado::Caminando:
                   r.ani->animar("caminar",true);
               break;
               case Personaje::Estado::Saltando:
                   r.ani->animar("saltar",true);
               break;
               case Personaje::Estado::Cayendo:
                   r.ani->animar("caer",true);
               break;
               case Personaje::Estado::Corriendo:
                   r.ani->animar("correr",true);
               break;
               case Personaje::Estado::Parado:
                   r.ani->animar("parado",true);
               break;
           }
           r.ani->act(t.delta());
           r.mesh->dibujar(r.shader,r.ent->getMatModelo(),r.ani->getPose(),r.esq->bindPoses);
    //       r.mesh->dibujar(r.shaderBorde,r.ent->getMatModelo(),r.ani->getPose(),r.esq->bindPoses,false);
       }else{
           r.mesh->dibujar(r.shader,r.ent->getMatModelo());
  //         r.mesh->dibujar(r.shaderBorde,r.ent->getMatModelo(),false);
       }
   }
   if(repMapa->meshUnica){
       repMapa->meshUnica->dibujar(shaders[0].get(),mat4(1.0f));
   }else for(unique_ptr<MeshBloque>& mesh:repMapa->meshes){
       mesh->dibujar(shaders[0].get(),mat4(1.0f));
   }
}
