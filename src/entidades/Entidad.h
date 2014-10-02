#ifndef ENTIDAD_H
#define ENTIDAD_H
#include "includeglm.h"

class Entidad
{
     public:
          Entidad();
          virtual ~Entidad();
          glm::vec3 pos;
          glm::quat direccion;
          glm::mat4x4 getMatModelo();
          void rotar(glm::vec3 angulos);
          void moverA(glm::vec3 posicion);
          void desplazar(glm::vec3 desplazamiento);
     private:

};

#endif // ENTIDAD_H
