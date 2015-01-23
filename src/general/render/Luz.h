#ifndef _LUZ_H_
#define _LUZ_H_
#include "includeglm.h"
class Luz{
    public:
        glm::vec3 pos;
        glm::mat4 getMat(){return glm::mat4(1.0f);};
};
#endif
