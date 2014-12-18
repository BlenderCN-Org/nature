#include "Fisica.h"
#include "Colision.h"
#include "config.h"
using namespace std;
void Fisica::aplicar(Entidad& entidad,Mapa& mapa,float dt){
    entidad.vel+=glm::vec3(0,0,gravedad*dt*entidad.gravedad);
    Colision c;
    entidad.desplazar(entidad.vel*dt);
    if((c=col.revColision(entidad,mapa)).colisiona&&entidad.vel.z<0.0f){
        float velz=-entidad.vel.z*entidad.rebote;
        entidad.vel=glm::vec3(entidad.vel.x,entidad.vel.y,velz<0.01?0:velz);
       //entidad.vel=glm::vec3(entidad.vel.x,entidad.vel.y,0.0f);
       
        entidad.pos=glm::vec3(entidad.pos.x,entidad.pos.y,c.pos.z);
    }

    DEBUG(/*{{{*/
        cout<<entidad.vel<<endl;
    )/*}}}*/
}
