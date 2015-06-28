#include "Fisica.h"
#include "Colision.h"
#include "config.h"
using namespace std;
using namespace glm;
void Fisica::aplicar(Entidad& entidad,Mapa& mapa,float dt){
    vec3 ace=entidad.ace+vec3(0.0f,0.0f,gravedad*entidad.gravedad);
//    ace=entidad.ace;
    entidad.vel+=ace*dt;
    vec3 pact=entidad.pos;
//    cout<<"ace.z"<<entidad.vel.z<<endl;
    entidad.desplazar(entidad.vel*dt);
    ivec3 pos=ivec3(round(entidad.pos.x),round(entidad.pos.y),round(entidad.pos.z));
    if(mapa.enRango(pos.x,pos.y,pos.z)&&mapa.enRango(pos.x,pos.y,pos.z+1)){
        Voxel v=mapa.getVoxel(pos.x,pos.y,pos.z);
        Voxel v2=mapa.getVoxel(pos.x,pos.y,pos.z+1);
        Voxel v3=mapa.getVoxel(pos.x,pos.y,pos.z+2);
        if(v.solido()){
            //entidad.pos=pact;
            if(!v2.solido()||!v3.solido()){
                Cubo c=mapa.getCuboVoxel(pos.x,pos.y,pos.z);
                if(v2.solido())
                    entidad.pos.z=pos.z+1+(mapa.getTamCubo()/2.0f);
                else
                    entidad.pos.z=pos.z+(mapa.getTamCubo()/2.0f);
                entidad.vel.z=0;
            }else{
                entidad.pos=pact;
                entidad.vel=vec3(0,0,0);
            }
        };
    }
    vector<Colision> colisiones=col.revColision(entidad,mapa);
    /*for(Colision c:colisiones){
        if(entidad.destruye){
            entidad.pos=vec3(entidad.pos.x,c.adir.y==0?entidad.pos.y:pact.y,c.adir.z==0?entidad.pos.z:c.pos.z);
            entidad.vel=vec3(entidad.vel.x,c.adir.y==1?0:entidad.vel.y,c.adir.z==1?0:entidad.vel.z);
        }else{
           entidad.pos=vec3(c.adir.x==0?entidad.pos.x:pact.x,c.adir.y==0?entidad.pos.y:pact.y,c.adir.z==0?entidad.pos.z:c.pos.z);
            entidad.vel=vec3(c.adir.x==1?0:entidad.vel.x,c.adir.y==1?0:entidad.vel.y,c.adir.z==1?0:entidad.vel.z);
            mapa.getVoxel
        }
    }*/
    entidad.ace=vec3(0,0,0);
    DEBUG(/*{{{*/
        cout<<entidad.vel<<endl;
    )/*}}}*/
}
