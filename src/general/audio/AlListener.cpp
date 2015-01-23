#include "AlListener.h"

void AlListener::setPos(glm::vec3 p){
    alListener3f(AL_POSITION, p.x,p.y,p.z);
}
void AlListener::setVel(glm::vec3 v){
    alListener3f(AL_VELOCITY, v.x, v.y,v.z);
}
void AlListener::setOri(glm::vec3 o){
    alListener3f(AL_ORIENTATION, o.x, o.y,o.z);
}
