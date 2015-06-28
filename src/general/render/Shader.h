#ifndef __SHADER_H
#define __SHADER_H

#include <string>
#include "openglnat.h"
#include "includeglm.h"
#include <vector>
#include <map>
#include "Textura.h"

class Shader {
public:
     Shader();
     Shader(const std::string& vsFile,const std::string& fsFile,std::map<std::string,std::string> vars={});
     ~Shader();
     Shader(const Shader&)=delete;
     Shader& operator=(const Shader&) = delete;
     Shader(Shader&&);
     Shader& operator=(Shader&&);

    int loc(std::string n);
    void setint(std::string n,int v);
    void setint(std::string n,std::vector<int> &v);
    void setint(std::string n,int size,int* v);

    void setfloat(std::string n,float v);
    void setfloat(std::string n,std::vector<float> &v);
    void setfloat(std::string n,int size,float* v);
    /**vec2***/
    void setvec2(std::string n,glm::vec2 v);
    void setvec2(std::string n,std::vector<glm::vec2> &v);
    void setvec2(std::string n,int size,float* v);
    /**vec3***/
    void setvec3(std::string n,glm::vec3 v);
    void setvec3(std::string n,std::vector<glm::vec3> &v);
    void setvec3(std::string n,int size,float* v);
    /**vec4***/
    void setvec4(std::string n,glm::vec4 v);
    void setvec4(std::string n,std::vector<glm::vec4> &v);
    void setvec4(std::string n,int size,float* v);
    /***Mat3***/
    void setmat3(std::string n,glm::mat3 v);
    void setmat3(std::string n,std::vector<glm::mat3> &v);
    void setmat3(std::string n,int size,float* v);
    /***Mat4***/
    void setmat4(std::string n,glm::mat4 v);
    void setmat4(std::string n,std::vector<glm::mat4> &v);
    void setmat4(std::string n,int size,float* v);
    void settexture(std::string n,int i,Textura& t);
    void init(const std::string& vsFile, const std::string& fsFile,std::map<std::string,std::string> vars={});
     
     void bind(const glm::mat4 &matModelo);
     void bind();
     void bind(const glm::mat4 &matModelo,std::vector<glm::mat4> pose,std::vector<glm::mat4> bindPoses);
     void unbind();

     unsigned int id();
     glm::mat4 matProy;
     glm::mat4 matVista;
     glm::mat4 matLuz;
     glm::vec3 vecVista;
     glm::vec3 luz;
     bool usarTex=false;
     Textura* tex;
     Textura* shadowMap;

private:
	unsigned int shader_id;
	unsigned int shader_vp;
	unsigned int shader_fp;


	 int projectionMatrixLocation;
     int viewMatrixLocation;
     int viewMatrixInvLocation;
     int modelMatrixLocation;
     int normalMatrixLocation;
     int poseMatrixLocation;
     int vecVistaLocation;
     int textureLocation;
     int luzLocation;
     int luzMatrixLocation;
     int shadowMapLocation;
};

#endif
