#ifndef _HUESO_H_
#define _HUESO_H_
#include "includeglm.h"
#include "fisica/Esfera.h"
#include <vector>
#include <string>
class Hueso{
    public:
       std::string nombre;
       int padre;
       glm::vec3 cabeza;
       glm::vec3 cola;
       glm::mat4 mat;
       int coli;
       std::vector<Esfera> getEsferas();
       
};
#endif
