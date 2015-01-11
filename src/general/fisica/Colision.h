#ifndef _COLISION_H_
#define _COLISION_H_
#include "includeglm.h"

class Colision{
    public:
        bool colisiona;
        glm::vec3  vel;
        glm::vec3 pos;
        glm::vec3 adir;//dir absoluta solo un eje tiene uno de los 3 ejes tiene los valores 1 o -1 los 2 ejes restantes tienen 0
        glm::vec3 rdir;
};

#endif
