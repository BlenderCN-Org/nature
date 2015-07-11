#include "RepEnt.h"
#include "entidades/Entidad.h"
#include "entidades/Personaje.h"
#include "shaders/ShaTexture.h"
using namespace std;
using namespace glm;

void RepEnt::dibujar(Entidad* ent,Camara& cam,Luz& l){
  sha->bind();
  ShaBasic::setProjMat(*sha,cam.getMatProy());
  ShaBasic::setViewMat(*sha,cam.getMatVista());
  ShaBasic::setViewMatInv(*sha,inverse(cam.getMatVista()));
  ShaBasic::setModelMat(*sha,ent->getMatModelo());
  ShaBasic::setNormalMat(*sha,transpose(inverse(ent->getMatModelo())));
  ShaBasic::setVecVista(*sha,cam.getOrientacion());
  ShaBasic::setVecLuz(*sha,l.pos);
  if(tex.get()!=nullptr)
      ShaTexture::setTexColor(*sha,*tex);
  mesh->dibujar();
 // cout<<"dibujando"<<endl;

};
void RepEnt::act(float dt){
};

