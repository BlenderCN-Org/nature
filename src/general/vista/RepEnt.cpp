#include "RepEnt.h"
#include "entidades/Personaje.h"
using namespace std;
using namespace glm;
void RepEnt::dibujar(Camara& cam,Luz& l){
  sha->bind();
  sha->setmat4("projectionMatrix" ,cam.getMatProy());
  sha->setmat4("viewMatrix",cam.getMatVista()); 
  sha->setmat4("viewMatrixInv",inverse(cam.getMatVista()));
  sha->setmat4("modelMatrix",ent->getMatModelo());
  sha->setmat4("normalMatrix",transpose(inverse(ent->getMatModelo())));
  sha->setvec3("vecVista",cam.getOrientacion());
  sha->setvec3("luz",l.pos);
  if(esq){ 
      vector<mat4> bindPosesInv;
      vector<mat4> boneTransform;
      vector<mat4> normalBone;
      vector<mat4> pose=ani->getPose();
      for(int i=0;i<esq->bindPoses.size();i++){
          glm::mat4 &bp=esq->bindPoses[i];
          glm::mat4 &mp=pose[i];
          bindPosesInv.push_back(glm::inverse(bp));
          boneTransform.push_back(bp*mp*inverse(bp));
          normalBone.push_back(transpose(inverse(ent->getMatModelo()*bp*mp*inverse(bp))));
      }
      sha->setmat4("poseMatrix",pose);
      sha->setmat4("bindPose",esq->bindPoses);
      sha->setmat4("bindPoseInv",bindPosesInv);
      sha->setmat4("normalBone",normalBone);
      sha->setmat4("boneTransforms",boneTransform);
  }
  mesh->dibujar();
  
};
void RepEnt::act(float dt){
    if(esq){
        Personaje* p= (Personaje*) ent.get();
       switch(p->estado){
           case Personaje::Estado::Caminando:
               ani->animar("caminar",true);
           break;
           case Personaje::Estado::Saltando:
               ani->animar("saltar",true);
           break;
           case Personaje::Estado::Cayendo:
               ani->animar("caer",true);
           break;
           case Personaje::Estado::Corriendo:
               ani->animar("correr",true);
           break;
           case Personaje::Estado::Parado:
               ani->animar("parado",true);
           break;
       }
       ani->act(dt);
    }

}

