#ifndef ENTIDAD_H
#define ENTIDAD_H
#include "includeglm.h"
#include "mapa/Cubo.h"
#include "fisica/Colision.h"
#include <string>
#include "esqueleto/Hueso.h"
#include "esqueleto/Esqueleto.h"
#include "esqueleto/Animador.h"
class Entidad
{
     public:
          Entidad();
          virtual ~Entidad();
          std::string nombre="";
          glm::vec3 pos;
          glm::vec3 vel;
          glm::vec3 ace;
          glm::quat direccion;
          float gravedad=1.0f;//0- no Gravedad 1.0 -Gravedad normal 2.0- doble de gravedad
          float rebote=0.0f;//0- Sin Rebote  1.0 -Rebote sin perdida de energia 2.0- Rebote con Doble  energia
          glm::mat4x4 getMatModelo();
          Cubo getCubo();
          void rotar(glm::vec3 angulos);
          void moverA(glm::vec3 posicion);
          void desplazar(glm::vec3 desplazamiento);
          virtual void act(float dt){};
          virtual void colisiona(Colision c){};
          int h=-1;
          Entidad* e;
          Esqueleto* esq;
          Animador* a;
          bool destruye=false;
     private:

};

#endif // ENTIDAD_H
