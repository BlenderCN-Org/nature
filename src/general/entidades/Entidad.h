#ifndef ENTIDAD_H
#define ENTIDAD_H
#include "includeglm.h"
#include "mapa/Cubo.h"
#include <string>
class Entidad
{
     public:
          Entidad();
          virtual ~Entidad();
          std::string nombre="";
          glm::vec3 pos;
          glm::vec3 vel;
          glm::quat direccion;
          float gravedad=1.0f;//0- no Gravedad 1.0 -Gravedad normal 2.0- doble de gravedad
          float rebote=0.0f;//0- Sin Rebote  1.0 -Rebote sin perdida de energia 2.0- Rebote con Doble  energia
          glm::mat4x4 getMatModelo();
          Cubo getCubo();
          void rotar(glm::vec3 angulos);
          void moverA(glm::vec3 posicion);
          void desplazar(glm::vec3 desplazamiento);
     private:

};

#endif // ENTIDAD_H
