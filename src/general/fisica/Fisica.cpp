#include "Fisica.h"
#include "Colision.h"
#include "config.h"
using namespace std;
using namespace glm;
void Fisica::aplicar(Entidad& entidad,Mapa& mapa,float dt){
    vec3 ace=entidad.ace+vec3(0.0f,0.0f,gravedad*entidad.gravedad);
    entidad.vel+=ace*dt;
    vec3 pact=entidad.pos;
//    cout<<"ace.z"<<entidad.vel.z<<endl;
    entidad.desplazar(entidad.vel*dt);
    vector<Colision> colisiones=col.revColision(entidad,mapa);
    for(Colision c:colisiones){
//        cout<<"Z ant="<<pact.z<<"; Z act="<<entidad.pos.z<<endl;
        entidad.pos=vec3(c.adir.x==0?entidad.pos.x:pact.x,c.adir.y==0?entidad.pos.y:pact.y,c.adir.z==0?entidad.pos.z:c.pos.z);
        entidad.vel=vec3(c.adir.x==1?0:entidad.vel.x,c.adir.y==1?0:entidad.vel.y,c.adir.z==1?0:entidad.vel.z);
//        entidad.ace=vec3(c.adir.x==1?0:entidad.ace.x,c.adir.y==1?0:entidad.ace.y,c.adir.z==1?0:entidad.ace.z);
        //cout<<"dir.z:"<<c.adir.z<<" ; ace.z(2):"<<entidad.ace.z<<endl;
    }
    entidad.ace=vec3(0,0,0);

    DEBUG(/*{{{*/
        cout<<entidad.vel<<endl;
    )/*}}}*/
}
