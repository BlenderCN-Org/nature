#ifndef ENTIDAD_H
#define ENTIDAD_H
#include "includeglm.h"
#include "mapa/Cubo.h"
class Entidad
{
     public:
          Entidad();
          virtual ~Entidad();
          glm::vec3 pos;
          glm::vec3 vel;
          glm::quat direccion;
          glm::mat4x4 getMatModelo();
          Cubo getCubo();
          void rotar(glm::vec3 angulos);
          void moverA(glm::vec3 posicion);
          void desplazar(glm::vec3 desplazamiento);
     private:

};

#endif // ENTIDAD_H
