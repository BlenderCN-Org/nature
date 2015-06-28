#include "CamSegPaj.h"
#include "includeglm.h"
using namespace glm;
using namespace std;
CamSegPaj::CamSegPaj(glm::vec3 r,Entidad* o,Entidad* s,Camara* c){
    cam=c;
    seguido=s;
    origen=o;
    rot=r;
}
void CamSegPaj::ejes(float x,float z){
 rot+=glm::vec3((maxx-minx)*x,0,(maxz-minz)*z);
 if(rot.x<minx) rot.x=minx;
 if(rot.x>maxx) rot.x=maxx;
// if(rot.z>maxz) rot.z=maxz;
// if(rot.z<minz) rot.z=minz;
};
void CamSegPaj::zoom(float z){
};
void CamSegPaj::movimiento(float x,float y,float z){
};
void CamSegPaj::act(float dt){
        vec3 vr=vec3(glm::rotate(mat4(1.0),radians(rot.z*0),vec3(0,0,1))*vec4(0,5,15,0));
        vec3 dir=(seguido->pos-origen->pos);
        dir=normalize(vec3(dir.x,dir.y,0));
    //    cout<<"Rotada: "<<rot.z<<";"<<vr.x<<","<<vr.y<<","<<vr.z<<endl;
        cam->pos= glm::vec3(origen->pos.x-vr.x,origen->pos.y-vr.y,origen->pos.z+vr.z);
        int t=55;
        int cx=floor(seguido->pos.x/t);
        int cy=floor(seguido->pos.y/t);
      //  cam->pos=glm::vec3(cx*t+t/2,cy*t+t/2,70);


        vec3 euler=degrees(eulerAngles(toQuat(lookAt(cam->pos,origen->pos,vec3(0,0,1)))));
        vec3 rotz=eulerAngles(glm::rotation(vec3(0,1,0),dir)) *  180.f/3.14159f ;
        cam->rot=glm::vec3(0.0f,0.0f,0.0f);
        cam->rot=vec3(20,0,rot.z*0);
}
