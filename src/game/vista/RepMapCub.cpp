#include "RepMapCub.h"
#include <iostream>
#include "includeglm.h"
#include "shaders/ShaBasic.h"
#include "shaders/ShaTexture.h"
using namespace std;
using namespace glm;
RepMapCub::RepMapCub(Mapa& m)
:mapa(m)
{
    meshCubo=MeshManager::instance()->load("cubo",Path::mesh("cubo"));
}

RepMapCub::~RepMapCub()
{}
void RepMapCub::dibujar(Camara& cam,Luz& l){
  sha->bind();
  ShaBasic::setProjMat(*sha,cam.getMatProy());
  ShaBasic::setViewMat(*sha,cam.getMatVista());
  ShaBasic::setViewMatInv(*sha,inverse(cam.getMatVista()));

  ShaBasic::setVecVista(*sha,cam.getOrientacion());
  ShaBasic::setVecLuz(*sha,l.pos);
  ShaTexture::setTexColor(*sha,*tex);
// cout<<"tam("<<mapa.getTamX()<<","<<mapa.getTamY()<<","<<mapa.getTamZ()<<")"<<endl;
  for(int x=cam.pos.x-20;x<cam.pos.x+20;x++){
     for(int y=cam.pos.y-20;y<cam.pos.y+20;y++){
//  for(int x=0;x<mapa.getTamX();x++){
  //   for(int y=0;y<mapa.getTamY();y++){
         for(int z=0;z<mapa.getTamZ();z++){
             if(mapa.enRango(x,y,z)){
                 Voxel& v=mapa.getVoxel(x,y,z);
                 if(v.borde){
        //               cout<<"dibujado"<<endl;
                     mat4 mat=translate(mat4(1.0),vec3(x,y,z));
        //                 mat=translate(mat4(1.0),vec3(100,10,10));
                     ShaBasic::setModelMat(*sha,mat);
                     ShaBasic::setNormalMat(*sha,transpose(inverse(mat)));
                     meshCubo->dibujar();
                 }
             }
          }
     }
    }
}
