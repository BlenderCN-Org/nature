#include "MeshDatos.h"
#include <iostream>
#include <fstream>
#include <memory>
#include "util/GestorRutas.h"
using namespace std;
using namespace glm;
MeshDatos::MeshDatos(std::string nombre){
    cargar(nombre);
}

MeshDatos::MeshDatos(){
}

void MeshDatos::cargar(std::string nombre){
    ifstream f;
    int nvert;
    int ncaras;
    f.open(GestorRutas::getRutaMesh(nombre),  ios::in |  ios::binary);
    if(!f.is_open()){
       cout<<"error abriendo"<<GestorRutas::getRutaMesh(nombre)<< endl;
    }else{
        f.read((char*)&nvert,sizeof(int));
          cout<<sizeof(int)<<":vertices="<<nvert<< endl;
          vert.resize(nvert);
          normal.resize(nvert);
          color.resize(nvert);
          hueso.resize(nvert);
          peso.resize(nvert);
        if(nvert>0){
           f.read((char*)&vert[0],sizeof(vec3)*nvert);
           f.read((char*)&normal[0],sizeof(vec3)*nvert);
           f.read((char*)&color[0],sizeof(vec3)*nvert);
           f.read((char*)&hueso[0],sizeof(float)*nvert);
           f.read((char*)&peso[0],sizeof(float)*nvert);
           f.read((char*)&ncaras,sizeof(int));
           uv.resize(nvert,vec2(0,0));
           oclusion.resize(nvert,vec4(0,0,0,0));
           if(ncaras>0){
               caras.resize(ncaras*3);
               f.read((char*)&caras[0],sizeof(GLuint)*ncaras*3);
           }
        }
    }

}
MeshDatos MeshDatos::plano(float ancho,float alto){
    MeshDatos d;
    int nv=4;
    int nc=2;
    d.vert.resize(nv);
    d.normal.resize(nv,vec3(0,0,1));
    d.color.resize(nv,vec3(1,1,1));
    d.hueso.resize(nv,0);
    d.peso.resize(nv,0);
    d.uv.resize(nv);
    d.caras.resize(nc);

    d.vert[0]=vec3(0,0,0);
    d.uv[0]=vec2(0,0);
    d.vert[1]=vec3(0,alto,0);
    d.uv[1]=vec2(0,1);
    d.vert[2]=vec3(ancho,alto,0);
    d.uv[2]=vec2(1,1);
    d.vert[3]=vec3(ancho,0,0);
    d.uv[3]=vec2(1,0);

    d.caras[0]=ivec3(0,2,1);
    d.caras[1]=ivec3(0,3,2);

    return move(d);
}
MeshDatos MeshDatos::linea(glm::vec3 v){
    MeshDatos d;
    int nv=4;
    int nc=4;
    d.vert.resize(nv);
    d.normal.resize(nv,vec3(0,0,1));
    d.color.resize(nv,vec3(1,1,1));
    d.hueso.resize(nv,0);
    d.peso.resize(nv,0);
    d.uv.resize(nv);
    d.caras.resize(nc);

    d.vert[0]=vec3(0,0,0);
    d.uv[0]=vec2(0,0);
    d.vert[1]=v;
    d.uv[1]=vec2(0,0);
    d.vert[2]=vec3(v.x+1,v.y,v.z);
    d.uv[2]=vec2(0,0);
    d.vert[3]=vec3(1,0,0);
    d.uv[3]=vec2(0,0);

    d.caras[0]=ivec3(0,2,1);
    d.caras[1]=ivec3(0,3,2);
    d.caras[2]=ivec3(0,1,2);
    d.caras[3]=ivec3(0,2,3);

    return move(d);

};
