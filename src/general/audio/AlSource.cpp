#include "AlSource.h"
#include "AL.h"
#include <iostream>
using namespace std;
AlSource::AlSource(){
 cout<< "Creando Source"<<endl;
  alGenSources(1, &source);
  cout<<OpenAl::error()<<endl;
 cout<< "Source Creado"<<endl;
}
AlSource::~AlSource(){
  alDeleteSources(1, &source);
}
void AlSource::setPitch(float v){
   alSourcef(source,AL_PITCH,v); 
   cout<<OpenAl::error()<<endl;
}
void AlSource::setGain(float v){
   alSourcef(source,AL_GAIN,v); 
   cout<<OpenAl::error()<<endl;
}
void AlSource::setPos(glm::vec3 p){
   alSource3f(source,AL_POSITION,p.x,p.y,p.z); 
   cout<<OpenAl::error()<<endl;
}
void AlSource::setVel(glm::vec3 v){
   alSource3f(source,AL_VELOCITY,v.x,v.y,v.z); 
   cout<<OpenAl::error()<<endl;
}
void AlSource::setLoop(bool l){
   alSourcei(source, AL_LOOPING, l?AL_TRUE:AL_FALSE);
}
void AlSource::play(AlBuffer& b){
   alSourceStop(source);
   alSourcei(source, AL_BUFFER, b.id());
   alSourcePlay(source);
}
