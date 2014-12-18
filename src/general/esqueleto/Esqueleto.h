#ifndef _ESQUELETO_H_
#define _ESQUELETO_H_
#include <vector>
#include <string>
#include "Hueso.h"
#include "AnimEsqueleto.h"
#include "includeglm.h"

class Esqueleto{
    public:
        std::vector<Hueso> huesos;
        std::vector<glm::mat4> bindPoses;
        std::vector<AnimEsqueleto> anims;
        Esqueleto(std::string ruta);
        virtual ~Esqueleto();
        std::vector<glm::mat4> getPose(std::string animacion,float t);
};

#endif
