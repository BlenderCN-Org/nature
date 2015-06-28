#include "RepMap.h"
#include <iostream>
#include "includeglm.h"
#include "shaders/ShaBasic.h"
using namespace std;
using namespace glm;
RepMap::RepMap(Mapa& m)
:mapa(m)
{
     meshes.reserve(mapa.bloques.size());
     for(int x=0;x<mapa.getBloquesX();x++){
         for(int y=0;y<mapa.getBloquesY();y++){
             for(int z=0;z<mapa.getBloquesZ();z++){
                 Bloque &b=mapa.bloques[z*mapa.getBloquesZ()+y*mapa.getBloquesY()+x];
                 if(b.borde){
                     meshes.push_back(unique_ptr<Mesh>{new Mesh(MeshBloque::generar(mapa,b))});
                 }
              }
         }
     }
/*     for(Bloque& b:mapa.bloques){
         if(b.borde){
             meshes.push_back(unique_ptr<Mesh>{new Mesh(MeshBloque::generar(mapa,b))});
         }
     }*/
//     cout<<"Meshes: "<<meshes.size()<<" Bloques"<<mapa.bloques.size()<<endl;
}

RepMap::~RepMap()
{
}
void RepMap::dibujar(Camara& cam,Luz& l){
  sha->bind();
  ShaBasic::setProjMat(*sha,cam.getMatProy());
  ShaBasic::setViewMat(*sha,cam.getMatVista());
  ShaBasic::setViewMatInv(*sha,inverse(cam.getMatVista()));
  ShaBasic::setModelMat(*sha,mat4(1.0f));
  ShaBasic::setNormalMat(*sha,transpose(inverse(mat4(1.0f))));
  ShaBasic::setVecVista(*sha,cam.getOrientacion());
  ShaBasic::setVecLuz(*sha,l.pos);
/*  sha->setmat4("projectionMatrix" ,cam.getMatProy());
  //sha->setmat4("viewMatrix",cam.getMatVista()); 
  sha->setmat4("viewMatrixInv",inverse(cam.getMatVista()));
  sha->setmat4("modelMatrix",mat4(1.0f));
  sha->setmat4("normalMatrix",transpose(inverse(mat4(1.0f))));
  sha->setvec3("vecVista",cam.getOrientacion());
  sha->setvec3("luz",l.pos);*/
  for(auto& mesh:meshes){
      mesh->dibujar();
  }

}
