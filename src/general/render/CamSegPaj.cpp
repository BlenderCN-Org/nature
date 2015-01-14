#include "CamSegPaj.h"
#include "includeglm.h"
using namespace glm;
using namespace std;
CamSegPaj::CamSegPaj(glm::vec3 r,Entidad* e,Camara* c){
    cam=c;
    seguido=e;
    rot=r;
}
void CamSegPaj::ejes(float x,float z){
 rot+=glm::vec3((maxx-minx)*x,0,(maxz-minz)*z);
 if(rot.x<minx) rot.x=minx;
 if(rot.x>maxx) rot.x=maxx;
 if(rot.z>maxz) rot.z=maxz;
 if(rot.z<minz) rot.z=minz;
};
void CamSegPaj::zoom(float z){

};
void CamSegPaj::movimiento(float x,float y,float z){
    

};
void CamSegPaj::act(float dt){
    vec3 vr=toMat3(quat(radians(vec3(0,0,0))))*vec3(-15,1,5);
//    cout<<"Rotada: "<<rot.z<<";"<<vr.x<<","<<vr.y<<","<<vr.z<<endl;
    cam->pos= glm::vec3(seguido->pos.x+vr.x,seguido->pos.y+vr.y,seguido->pos.z+vr.z);
    vec3 euler=degrees(eulerAngles(toQuat(lookAt(cam->pos,seguido->pos,vec3(0,0,1)))));
    cam->rot=glm::vec3(rot.x,0.0f,rot.z);
  //  cout<<"euler: "<<euler.x<<","<<euler.y<<","<<euler.z<<endl;
//    cam->rot=vec3(euler.x,0.0f,euler.z);
}
