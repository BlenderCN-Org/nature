#ifndef _AL_LISTENER_H_
#define _AL_LISTENER_H_
#include "includeglm.h"
#include <AL/al.h>
#include <AL/alc.h>
class AlListener{
    public:
        void setPos(glm::vec3 p);
        void setVel(glm::vec3 v);
        void setOri(glm::vec3 o);
};
#endif
