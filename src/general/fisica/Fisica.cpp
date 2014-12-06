#include "Fisica.h"
#include "Colision.h"
#include "config.h"
using namespace std;
void Fisica::aplicar(Entidad& entidad,Mapa& mapa,float dt){
    entidad.vel+=glm::vec3(0,0,gravedad*dt);
    Colision c;
    if((c=col.revColision(entidad,mapa)).colisiona&&entidad.vel.z<0){
        entidad.vel=glm::vec3(entidad.vel.x,entidad.vel.y,-entidad.vel.z*0.8);
        entidad.vel=glm::vec3(entidad.vel.x,entidad.vel.y,0);
       
        entidad.pos=glm::vec3(entidad.pos.x,entidad.pos.y,c.pos.z);
    }
    DEBUG(/*{{{*/
        cout<<entidad.vel<<endl;
    )/*}}}*/
    entidad.desplazar(entidad.vel*dt);
}
