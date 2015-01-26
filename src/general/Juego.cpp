#include "Juego.h"
#include <chrono>
#include <iostream>
#include "mapa/Generador.h"
#include "includeglm.h"
#include "vista/RepMap.h"
#include "vista/RepPer.h"
#include "vista/RepEne.h"
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
camara(45.0f, 1024.0f / 680.0f, 1.0f, 2000.f),
shadowMap(2048,2048) 
{
    rep.reserve(10);

//     buffer=move(OggBuffer::cargar(Path::res("Bomb.ogg")));
     listener.setPos(vec3(0,0,0));
     listener.setVel(vec3(0,0,0));
     listener.setOri(vec3(0,0,-1));
     source.setPos(vec3(1,0,0));
     source.setGain(1.0);
     source.setPitch(1.0);
     source.setLoop(true);
     source.setVel(vec3(0,0,0));
     //source.play(buffer);

     luz.pos=vec3(-0.2,-1,0.6);
     
     unique_ptr<RepEnt> repCubico= unique_ptr<RepEnt>(new RepPer());
     repCubico->mesh=unique_ptr<Mesh>(new Mesh(MeshDatos("cubico")));
     repCubico->ent=unique_ptr<Entidad>(new Personaje());
     repCubico->esq=unique_ptr<Esqueleto>(new Esqueleto("cubico.mesh.esq"));
     repCubico->ani=unique_ptr<Animador>(new Animador(*repCubico->esq));
     repCubico->ani->animar("correr",true);
     repCubico->ent->gravedad=2.0f;
     repCubico->ent->pos=vec3(46,10,20);
     repCubico->ent->rebote=0.0f;
     repCubico->ent->vel=vec3(0.0f,0.0f,02.0f);
     repCubico->ent->ace=vec3(0.0f,0.0f,0.0f);
     repCubico->ent->rotar(vec3(0,0,180));
     repCubico->sha=unique_ptr<Shader>(new Shader(Path::shader("animado.vert"),Path::shader("basico.frag"),map<string,string>{{"%nhuesos%","6"}}));

     unique_ptr<RepEnt> repMonster= unique_ptr<RepEnt>(new RepEne());
     repMonster->mesh=unique_ptr<Mesh>(new Mesh(MeshDatos("monstruo")));
     repMonster->ent=unique_ptr<Entidad>(new Monstruo());
     cout<<"Ppersonaje"<<((Monstruo*)repMonster.get())->p<<endl; 
     repMonster->esq=unique_ptr<Esqueleto>(new Esqueleto("monstruo.mesh.esq"));
     repMonster->ani=unique_ptr<Animador>(new Animador(*repMonster->esq));
     repMonster->ani->animar("caminar",true);
     repMonster->ent->gravedad=2.0f;
     repMonster->ent->pos=vec3(49,90,20);
     repMonster->ent->rebote=0.0f;
     repMonster->ent->vel=vec3(0.0f,0.0f,02.0f);
     repMonster->ent->ace=vec3(0.0f,0.0f,0.0f);
     repMonster->sha=unique_ptr<Shader>(new Shader(Path::shader("animado.vert"),Path::shader("basico.frag"),map<string,string>{{"%nhuesos%","6"}}));

     unique_ptr<RepEnt> repEspada= unique_ptr<RepEnt>(new RepEnt());
     repEspada->mesh=unique_ptr<Mesh>(new Mesh(MeshDatos("espada")));
     repEspada->ent=unique_ptr<Entidad>(new Entidad());
     repEspada->ent->gravedad=0.0f;
     repEspada->ent->pos=vec3(45,25,18.6);
     repEspada->ent->rebote=0.0f;
     repEspada->ent->vel=vec3(0.0f,0.0f,0.0f);
     repEspada->ent->ace=vec3(0.0f,0.0f,0.0f);
     repEspada->ent->rotar(vec3(180,12,0));
     repEspada->sha=unique_ptr<Shader>(new Shader(Path::shader("basico.vert"),Path::shader("basico.frag")));



     unique_ptr<RepEnt> repJaula= unique_ptr<RepEnt>(new RepEne());
     repJaula->mesh=unique_ptr<Mesh>(new Mesh(MeshDatos("jaula")));
     repJaula->ent=unique_ptr<Entidad>(new Entidad());
     repJaula->esq=unique_ptr<Esqueleto>(new Esqueleto("jaula.mesh.esq"));
     repJaula->ani=unique_ptr<Animador>(new Animador(*repJaula->esq));
     repJaula->ani->animar("cerrada",true);
     repJaula->ent->gravedad=2.0f;
     repJaula->ent->pos=vec3(49,95,11);
     repJaula->ent->rebote=0.0f;
     repJaula->ent->vel=vec3(0.0f,0.0f,09.0f);
     repJaula->ent->ace=vec3(0.0f,0.0f,0.0f);
     repJaula->sha=unique_ptr<Shader>(new Shader(Path::shader("animado.vert"),Path::shader("basico.frag"),map<string,string>{{"%nhuesos%","5"}}));



     ctrCam=unique_ptr<ControlCamara>(new CamSegPaj(vec3(90,0,-22),repCubico->ent.get(),repMonster->ent.get(),&camara));
     rep.push_back(move(repCubico));
     rep.push_back(move(repMonster));
     rep.push_back(move(repEspada));
    // rep.push_back(move(repJaula));

/*     rep[2]->ent->h=rep[0]->esq->getHueso();
     rep[2]->ent->esq=rep[0]->esq.get();
     rep[2]->ent->e=rep[0]->ent.get();
     rep[2]->ent->a=rep[0]->ani.get();*/
     ((Monstruo*)rep[1]->ent.get())->p=(Personaje*) rep[0]->ent.get();
    //rep.push_back(move(repEjes));
    //rep.push_back(move(repDragon));
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
void Juego::tomarEspada(){
    if(Colisionador::revColision(*rep[0]->ent.get(),*rep[2]->ent.get()).colisiona){
        rep[2]->ent->direccion=quat(0,0,0,1);
        rep[2]->ent->pos=vec3(0,0,0);

         rep[2]->ent->h=rep[0]->esq->getHueso();
         rep[2]->ent->esq=rep[0]->esq.get();
         rep[2]->ent->e=rep[0]->ent.get();
         rep[2]->ent->a=rep[0]->ani.get();
         ((Monstruo*)rep[1]->ent.get())->estado=Monstruo::Estado::Detenido;
    }
}


void Juego::movimiento(float x,float y,float z){
     //camara.desplazar(vec3(x*t.delta(),y*t.delta(),z*t.delta()));
     if(lateral){
         Personaje* p=(Personaje*) rep[0]->ent.get();
         p->ejesMover(-y,0);
     }else{
         vec3 v=vec3(x,y,0);
         Personaje* p=(Personaje*) rep[0]->ent.get();
         vec3 vmov=camara.leftXY()*-x+camara.forwardXY()*y;
         p->ejesMover(-vmov.y,vmov.x);
     }
};
void Juego::presionaSalto(){
     Personaje* p=(Personaje*) rep[0]->ent.get();
     p->iniciarSalto();
}; 
void Juego::atacar(){
     Personaje* p=(Personaje*) rep[0]->ent.get();
     if(!lateral){
        p->atacar();
     }
     
}; 
void Juego::esquivar(){
     Personaje* p=(Personaje*) rep[0]->ent.get();
     p->esquivar();
}; 

void Juego::sueltaSalto(){
     Personaje* p=(Personaje*) rep[0]->ent.get();
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
     MeshDatos md("coliseo");
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
   if(rep[0]->ent->pos.x>105){
       if(!lateral){
           lateral=true;
           ((CamSegPaj* )ctrCam.get())->lateral=true;
           rep[1]->ent->pos.y=59;
           rep[1]->ent->pos.x=90;
           rep[1]->ent->pos.z=17;
           rep[1]->ent->vel=vec3(0,0,0);
           ((Monstruo*)rep[1]->ent.get())->estado=Monstruo::Estado::Detenido;
           ((Monstruo*)rep[1]->ent.get())->lateral=true;
           ((Monstruo*)rep[1]->ent.get())->destruye=true;
           ((Personaje*)rep[0]->ent.get())->lateral=true;
       }
   }else{
       lateral=false;
       ((CamSegPaj* )ctrCam.get())->lateral=false;
   }
   while(tacumf>0.02f){
       tomarEspada();
       colisionPersonajes();
       for (auto &r:rep){
           fisica.aplicar(*r->ent,mapa,0.02f);
           r->ent->act(0.02f);
//           if(r->ent->pos.z<0){
//                r->ent->pos=vec3(20,20,40);
//           }

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
   for (auto& r:rep){
          r->act(t.delta());
          r->dibujar(camara,luz);
   }
   repMapa->dibujar(camara,luz);
}




std::vector<Esfera> Juego::getEsferas(Hueso& h){
    vector<Esfera> es;
    for(int i=0;i<h.coli;i++){
      Esfera e;
      float l=glm::distance(h.cabeza,h.cola);
      e.r=l/((float)h.coli)/2;
      vec3 v=(h.cola-h.cabeza);
      e.c=v/((float)h.coli)*((float)i)+v*e.r;
      es.push_back(e);
    } 
   return es;
}
void Juego::colisionPersonajes(){
    /** Dañar Enemigo*/
    RepPer* repPer=(RepPer*)rep[0].get();
    RepEne* repMons=(RepEne*)rep[1].get();
    Personaje* p=(Personaje*) rep[0]->ent.get();
    Monstruo* m=(Monstruo*)  rep[1]->ent.get();
    Esqueleto* ep=rep[0]->esq.get();
    Esqueleto* em=rep[1]->esq.get();
    int ihespa=ep->getHueso();
    vector<Esfera> esfEspa=getEsferas(ep->huesos[ihespa]);
//    vector<Esfera> esfEspa;
    if(p->estado==Personaje::Estado::Atacando){
        for(int i=0;i<em->huesos.size();i++){
            Hueso &h=em->huesos[i];
            vector<Esfera> esfMons= getEsferas(h);
            for(Esfera eEspa:esfEspa){ 
                mat4 pmp=repPer->ani->getPose()[ihespa];
                mat4 pmb=repPer->esq->bindPoses[ihespa];
                mat4 pm=repPer->ent->getMatModelo();
                eEspa.c=vec3(pm*pmb*pmp*vec4(eEspa.c,1));
                for(Esfera eMons:esfMons){
                    mat4 mmp=repMons->ani->getPose()[i];
                    mat4 mmb=repMons->esq->bindPoses[i];
                    mat4 mm=repMons->ent->getMatModelo();
                    eMons.c=vec3(mm*mmb*mmp*vec4(eMons.c,1));
                   Colision c=Colisionador::revColision(eEspa,eMons);
                   if(c.colisiona){
                       m->herir();
                       return;
                   }
                }
            }
        }
    }
    if(m->estado==Monstruo::Estado::AtaqueGirar||
       m->estado==Monstruo::Estado::AtaqueBomba
      ){

        for(int i=0;i<em->huesos.size();i++){
            Hueso &hm=em->huesos[i];
            vector<Esfera> esfMons= getEsferas(hm);
            for(int j=0;j<ep->huesos.size();j++){
                Hueso &hp=ep->huesos[j];
                vector<Esfera> esfPer= getEsferas(hp);
                for(Esfera ePer:esfPer){ 
                    mat4 pmp=repPer->ani->getPose()[j];
                    mat4 pmb=repPer->esq->bindPoses[j];
                    mat4 pm=repPer->ent->getMatModelo();
                    ePer.c=vec3(pm*pmb*pmp*vec4(ePer.c,1));
                    for(Esfera eMons:esfMons){
                        mat4 mmp=repMons->ani->getPose()[i];
                        mat4 mmb=repMons->esq->bindPoses[i];
                        mat4 mm=repMons->ent->getMatModelo();
                        eMons.c=vec3(mm*mmb*mmp*vec4(eMons.c,1));
                       Colision c=Colisionador::revColision(ePer,eMons);
                       if(c.colisiona){
                    //       if(m->estado!=Monstruo::Estado::AtaqueBomba||m->vel.z<0){
                              p->herir();
                      //     }
                           return;
                       }
                    }
                }
            }
        }
    }

}
