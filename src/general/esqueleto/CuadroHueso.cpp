#include "CuadroHueso.h"
#include <iostream>
using namespace std;
using namespace glm;


void imprimirMatriz2(glm::mat4 mat){
    for(int y=0;y<4;y++){
        cout<<"(";
        for(int x=0;x<4;x++){
            cout<<(x>0?",":"")<<mat[x][y];
        }
        cout<<")"<<endl;
    }
}

glm::mat4  CuadroHueso::getMat(){
     glm::mat4 m=glm::translate(glm::mat4(1.0),pos);
     m=m*glm::toMat4(rot);
     return m;
}

glm::mat4  CuadroHueso::getMatP(vector<Hueso> &huesos,vector<CuadroHueso> &cuadros,Hueso& h){
    Hueso& p=huesos[h.padre];
    CuadroHueso& chp=cuadros[h.padre];
    glm::mat4 mp=glm::mat4(1.0f);
    glm::mat4 mtp=glm::mat4(1.0f);
    glm::mat4 m=glm::mat4(1.0f);

    mp=glm::translate(glm::mat4(1.0f),chp.pos);
    mp=mp*glm::toMat4(chp.rot);
    mtp=translate(mat4(1.0f),vec3(mp*inverse(p.mat)*vec4(h.cabeza,1.0f)));
//    mtp=translate(mat4(1.0f),h.cabeza-p.cola)*mtp;
    m=mtp;
    if(p.padre>=0){
        //cout<<"calculando padre:"<<p.padre<<endl;
        m=getMatP(huesos,cuadros,p)*m;
    }
    return m;
}
glm::mat4  CuadroHueso::getMat(vector<Hueso> &huesos,vector<CuadroHueso> &cuadros,Hueso& h,int id){
     glm::mat4 mp=glm::mat4(1.0f);
     glm::mat4 m=glm::translate(glm::mat4(1.0),pos);
     m=m*glm::toMat4(rot);
     if(h.padre>=0){
        mp=inverse(h.mat)*getMatP(huesos,cuadros,h);
        m=m;
     }
     return m;
}
