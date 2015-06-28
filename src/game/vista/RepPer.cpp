#include "RepPer.h"
using namespace std;
using namespace glm;
void RepPer::dibujar(Entidad* ent,Camara& cam,Luz& l){
  RepSer::dibujar(ent,cam,l);
  shaArma->bind();
  ShaBasic::setProjMat(*shaArma,cam.getMatProy());
  ShaBasic::setViewMat(*shaArma,cam.getMatVista());
  ShaBasic::setViewMatInv(*shaArma,inverse(cam.getMatVista()));

  ShaBasic::setNormalMat(*shaArma,transpose(inverse(ent->getMatModelo())));
  ShaBasic::setVecVista(*shaArma,cam.getOrientacion());
  ShaBasic::setVecLuz(*shaArma,l.pos);

  Ser *ser=static_cast<Ser*>(ent);
  int hid=ser->esq.getHueso();
  vector<mat4> pose=ser->ani.getPose();
  ShaBasic::setModelMat(*shaArma,ent->getMatModelo()*ser->esq.bindPoses[hid]*pose[hid]);
  meshArma->dibujar();

};


