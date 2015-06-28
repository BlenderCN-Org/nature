#ifndef CAMARA_H
#define CAMARA_H
#include "includeglm.h"

class Camara
{
     public:
          Camara(float av,float proporcion,float cercano,float lejano);//av=fov
          virtual ~Camara();
          glm::mat4 getMatVista(){return glm::inverse(getMat());};
          glm::mat4 getMatProy(){return mProy;};
          glm::vec3 getOrientacion();
          glm::mat4 getMat();
          glm::vec3 forwardXY();
          glm::vec3 leftXY();
          void rotar(glm::vec3 v);
          void desplazar(glm::vec3 v);
          glm::vec3 rot{0,0,0};
          glm::vec3 pos{0,0,0};
     private:
          glm::mat4 mProy;
          
};

#endif // CAMARA_H
