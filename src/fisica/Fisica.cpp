#include "Fisica.h"
void Fisica::aplicar(Entidad& entidad,float dt){
    entidad.desplazar(glm::vec3(0,0,gravedad*dt));
}
