#ifndef _MATBASICO_H_
#define _MATBASICO_H_
#include <memory>
#include "render/Shader.h"
class ShaBasic{
    public:
        ShaBasic();
        static void setProjMat(Shader& sha,glm::mat4 mat);
        static void setViewMat(Shader& sha,glm::mat4 mat);
        static void setViewMatInv(Shader& sha,glm::mat4 mat);
        static void setModelMat(Shader& sha,glm::mat4 mat);
        static void setNormalMat(Shader& sha,glm::mat4 mat);
        static void setVecVista(Shader& sha,glm::vec3 mat);
        static void setVecLuz(Shader& sha,glm::vec3 mat);

        static void setPoseMat(Shader& sha,std::vector<glm::mat4> mats);
        static void setBindPose(Shader& sha,std::vector<glm::mat4> mats);
        static void setBindPoseInv(Shader& sha,std::vector<glm::mat4> mats);
        static void setNormalBone(Shader& sha,std::vector<glm::mat4> mats);
        static void setBoneTran(Shader& sha,std::vector<glm::mat4> mats);
        static void bind();
    protected:
        Shader sha;

};
#endif
