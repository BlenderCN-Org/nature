#ifndef _CAMSEGPAJ_H_
#define _CAMSEGPAJ_H_
#include "entidades/Entidad.h"
#include "Camara.h"
#include "control/ControlCamara.h"
class CamSegPaj:public ControlCamara{
    public:
       CamSegPaj(glm::vec3 r,Entidad* e,Camara* c);
       virtual void act(float dt);
       virtual void ejes(float x,float z);
       virtual void zoom(float z);
       virtual void movimiento(float x,float y,float z);
       Entidad* seguido;
       Camara* cam;
   private:
       glm::vec3 rot;
       float minx=32;
       float maxx=145;
       float minz=-179;
       float maxz=179;

};
#endif
