#include "ShaBasic.h"

void ShaBasic::setProjMat(Shader& sha,glm::mat4 mat){
  sha.setmat4("projectionMatrix" ,mat);
  
};
void ShaBasic::setViewMat(Shader& sha,glm::mat4 mat){
  sha.setmat4("viewMatrix",mat); 
}
void ShaBasic::setViewMatInv(Shader& sha,glm::mat4 mat){
  sha.setmat4("viewMatrixInv",mat);
}
void ShaBasic::setModelMat(Shader& sha,glm::mat4 mat){
  sha.setmat4("modelMatrix",mat);
}
void ShaBasic::setNormalMat(Shader& sha,glm::mat4 mat){
  sha.setmat4("normalMatrix",mat);
}
void ShaBasic::setVecVista(Shader& sha,glm::vec3 vec){
  sha.setvec3("vecVista",vec);
}
void ShaBasic::setVecLuz(Shader& sha,glm::vec3 vec){
  sha.setvec3("luz",vec);
}
void ShaBasic::setPoseMat(Shader& sha,std::vector<glm::mat4> mats){
    sha.setmat4("poseMatrix",mats);
};
void ShaBasic::setBindPose(Shader& sha,std::vector<glm::mat4> mats){
    sha.setmat4("bindPose",mats);
};
void ShaBasic::setBindPoseInv(Shader& sha,std::vector<glm::mat4> mats){
    sha.setmat4("bindPoseInv",mats);
};
void ShaBasic::setNormalBone(Shader& sha,std::vector<glm::mat4> mats){
    sha.setmat4("normalBone",mats);
}
void ShaBasic::setBoneTran(Shader& sha,std::vector<glm::mat4> mats){
    sha.setmat4("boneTransforms",mats);
}




