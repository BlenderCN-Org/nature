#include "AlSource.h"
AlSource::AlSource(){
  alGenSources(1, &source);
}
AlSource::~AlSource(){
  alDeleteSources(1, &source);
}
void AlSource::setPitch(float v){
   alSourcef(source,AL_PITCH,v); 
}
void AlSource::setGain(float v){
   alSourcef(source,AL_GAIN,v); 
}
void AlSource::setPos(glm::vec3 p){
   alSource3f(source,AL_POSITION,p.x,p.y,p.z); 
}
void AlSource::setVel(glm::vec3 v){
   alSource3f(source,AL_VELOCITY,v.x,v.y,v.z); 
}
void AlSource::setLoop(bool l){
   alSourcei(source, AL_LOOPING, l?AL_TRUE:AL_FALSE);
}
void AlSource::play(AlBuffer& b){
   alSourcei(source, AL_BUFFER, b.id());
   alSourcePlay(source);
}
