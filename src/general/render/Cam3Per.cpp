#include "Cam3Per.h"
#include "includeglm.h"
using namespace glm;
using namespace std;
Cam3Per::Cam3Per(glm::vec3 r,Entidad* o,Entidad* s,Camara* c){
    cam=c;
    seguido=s;
    origen=o;
    rot=r;
}
void Cam3Per::ejes(float x,float z){
 rot+=glm::vec3((maxx-minx)*x,0,(maxz-minz)*z);
 if(rot.x<minx) rot.x=minx;
 if(rot.x>maxx) rot.x=maxx;
// if(rot.z>maxz) rot.z=maxz;
// if(rot.z<minz) rot.z=minz;
};
void Cam3Per::zoom(float z){
};
void Cam3Per::movimiento(float x,float y,float z){
};
void Cam3Per::act(float dt){
    if(lateral){
      cam->pos=vec3(origen->pos.x,origen->pos.y-30,origen->pos.z);
      cam->rot=vec3(90,0,0);
    }else{
        vec3 vr=vec3(glm::rotate(mat4(1.0),radians(rot.z),vec3(0,0,1))*vec4(0,8,0,0));
        vec3 dir=(seguido->pos-origen->pos);
        dir=normalize(vec3(dir.x,dir.y,0));
    //    cout<<"Rotada: "<<rot.z<<";"<<vr.x<<","<<vr.y<<","<<vr.z<<endl;
        cam->pos= glm::vec3(origen->pos.x+-vr.x,origen->pos.y-vr.y,origen->pos.z+3);
        int t=55;
        int cx=floor(seguido->pos.x/t);
        int cy=floor(seguido->pos.y/t);
    //    cam->pos=glm::vec3(cx*t+t/2,cy*t+t/2,70);


        vec3 euler=degrees(eulerAngles(toQuat(lookAt(cam->pos,origen->pos,vec3(0,0,1)))));
        vec3 rotz=eulerAngles(glm::rotation(vec3(0,1,0),dir)) *  180.f/3.14159f ;
        cam->rot=glm::vec3(0.0f,0.0f,0.0f);
        cam->rot=vec3(rot.x,0,rot.z);
      //cout<<"euler: "<<euler.x<<","<<euler.y<<","<<euler.z<<endl;
      //cam->rot=vec3(euler.x,0.0f,euler.z);
  }
}
