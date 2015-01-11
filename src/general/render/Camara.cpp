#include "Camara.h"
using namespace glm;
Camara::Camara(float av,float proporcion,float cercano,float lejano)
{
     this->mProy=glm::perspective(glm::radians(av), proporcion, cercano, lejano);
}

void Camara::desplazar(glm::vec3 v){
    pos=pos+v;
}
void Camara::rotar(glm::vec3 v){
    rot.x+=v.x;
    rot.z+=v.z;
    rot.y+=v.y;
}
Camara::~Camara()
{
     //dtor
}
glm::mat4  Camara::getMat(){
     if(rot.x<0.1) rot.x=0.1;
     if(rot.x>179.9) rot.x=179.9;
     mat4 matRot =rotate(mat4(1.0),radians(rot.z),vec3(0,0,1))*rotate(mat4(1.0),radians(rot.x),vec3(1,0,0));
     return translate(mat4(1.0),pos)*matRot;
}

glm::vec3 Camara::getOrientacion(){
    return mat3(getMat())*glm::vec3(0.0f,0.0f,-1.0f);
}
