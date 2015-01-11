#include "Entidad.h"

Entidad::Entidad()
{
   vel=glm::vec3(0,0,0);
   direccion=glm::quat();
}

Entidad::~Entidad()
{
}
Cubo Entidad::getCubo(){
    Cubo c{glm::vec3(pos.x-0.9f,pos.y-0.9,pos.z),glm::vec3(1.8f,1.8f,2.0f)};
    return c;
}
glm::mat4  Entidad::getMatModelo(){
     glm::mat4 m=glm::translate(glm::mat4(1.0),pos);
     m=m*glm::mat4_cast(direccion);
     return m;
}
void Entidad::rotar(glm::vec3 angulos){
     direccion=direccion*glm::quat(glm::radians(angulos));
}
void Entidad::moverA(glm::vec3 posicion){
     pos=posicion;
}
void Entidad::desplazar(glm::vec3 desplazamiento){
     pos+=desplazamiento;
};
