#ifndef _ALSOURCE_H_
#define _ALSOURCE_H_
#include "includeglm.h"
#include <AL/al.h>
#include <AL/alc.h>
#include "AlBuffer.h"
class AlSource{
    public:
        AlSource();
        ~AlSource();
        void setPitch(float v);
        void setGain(float v);
        void setPos(glm::vec3 p);
        void setVel(glm::vec3 v);
        void setLoop(bool l);
        void play(AlBuffer& b);
    private:
        ALuint source;
};
#endif

