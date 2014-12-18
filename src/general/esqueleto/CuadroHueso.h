#ifndef _CUADRO_HUESO_H_
#define _CUADRO_HUESO_H_
#include "includeglm.h"
#include "Hueso.h"
#include <vector>
class CuadroHueso{
    public:
        glm::vec3 pos;
        glm::quat rot;
        glm::mat4  getMat();
        glm::mat4  getMat(std::vector<Hueso> &huesos,std::vector<CuadroHueso> &cuadros,Hueso& h,int id);
        glm::mat4  getMatP(std::vector<Hueso> &huesos,std::vector<CuadroHueso> &cuadros,Hueso& h);
};

#endif
