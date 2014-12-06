#ifndef CAMARA_H
#define CAMARA_H
#include "entidades/Entidad.h"
#include "includeglm.h"

class Camara: public Entidad
{
     public:
          Camara(float av,float proporcion,float cercano,float lejano);//av=fov
          virtual ~Camara();
          glm::mat4 getMatVista(){return glm::inverse(getMatModelo());};
          glm::mat4 getMatProy(){return mProy;};
     private:
          glm::mat4 mProy;
};

#endif // CAMARA_H
