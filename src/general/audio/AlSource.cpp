#include "AlSource.h"
#include "AL.h"
#include <iostream>
using namespace std;
AlSource::AlSource(){
  alGenSources(1, &source);
  cout<<"constructor"<<endl;
  cout<<OpenAl::error()<<endl;
}
AlSource::~AlSource(){
  cout<<"destructor:"<<source<<endl;
  alDeleteSources(1, &source);
}
void AlSource::setPitch(float v){
   alSourcef(source,AL_PITCH,v); 
  cout<<"pitch"<<endl;
   cout<<OpenAl::error()<<endl;
}
void AlSource::setGain(float v){
   alSourcef(source,AL_GAIN,v); 
  cout<<"gain"<<endl;
   cout<<OpenAl::error()<<endl;
}
void AlSource::setPos(glm::vec3 p){
   alSource3f(source,AL_POSITION,p.x,p.y,p.z); 
  cout<<"pos"<<endl;
   cout<<OpenAl::error()<<endl;
}
void AlSource::setVel(glm::vec3 v){
   alSource3f(source,AL_VELOCITY,v.x,v.y,v.z); 
  cout<<"vel"<<endl;
   cout<<OpenAl::error()<<endl;
}
void AlSource::setLoop(bool l){
   alSourcei(source, AL_LOOPING, l?AL_TRUE:AL_FALSE);
  cout<<"loop"<<endl;
   cout<<OpenAl::error()<<endl;
}
void AlSource::play(AlBuffer& b){
   alSourceStop(source);
   alSourcei(source, AL_BUFFER, b.id());
   cout<<"bind buffer"<<endl;
   cout<<OpenAl::error()<<endl;
   alSourcePlay(source);
   cout<<"play"<<endl;alSourceStop(source);
   cout<<OpenAl::error()<<endl;
}
