#include "RepSer.h"
#include "entidades/Entidad.h"
using namespace std;
using namespace glm;
void RepSer::dibujar(Entidad* ent,Camara& cam,Luz& l){
  sha->bind();
  ShaBasic::setProjMat(*sha,cam.getMatProy());
  ShaBasic::setViewMat(*sha,cam.getMatVista());
  ShaBasic::setViewMatInv(*sha,inverse(cam.getMatVista()));
  ShaBasic::setModelMat(*sha,ent->getMatModelo());
  ShaBasic::setNormalMat(*sha,transpose(inverse(ent->getMatModelo())));
  ShaBasic::setVecVista(*sha,cam.getOrientacion());
  ShaBasic::setVecLuz(*sha,l.pos);

  vector<mat4> bindPosesInv;
  vector<mat4> boneTransform;
  vector<mat4> normalBone;

  Ser *ser=static_cast<Ser*>(ent);
  vector<mat4> pose=ser->ani.getPose();
  for(int i=0;i<ser->esq.bindPoses.size();i++){
      glm::mat4 &bp=ser->esq.bindPoses[i];
      glm::mat4 &mp=pose[i];
      bindPosesInv.push_back(glm::inverse(bp));
      boneTransform.push_back(bp*mp*inverse(bp));
      normalBone.push_back(transpose(inverse(ent->getMatModelo()*bp*mp*inverse(bp))));
  }
  ShaBasic::setPoseMat(*sha,pose);
  ShaBasic::setBindPose(*sha,ser->esq.bindPoses);
  ShaBasic::setBindPoseInv(*sha,bindPosesInv);
  ShaBasic::setNormalBone(*sha,normalBone);
  ShaBasic::setBoneTran(*sha,boneTransform);
           
  mesh->dibujar();


};

void RepSer::act(float dt){
/*      if(ani!=nullptr)
       ani->act(dt);*/
};

