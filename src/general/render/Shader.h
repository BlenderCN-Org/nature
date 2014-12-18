#ifndef __SHADER_H
#define __SHADER_H

#include <string>
#include "openglnat.h"
#include "includeglm.h"
#include <vector>
#include <map>

class Shader {
public:
     Shader();
     Shader(const std::string& vsFile,const std::string& fsFile,std::map<std::string,std::string> vars={});
     ~Shader();
     Shader(const Shader&)=delete;
     Shader& operator=(const Shader&) = delete;
     Shader(Shader&&);
     Shader& operator=(Shader&&);

     void init(const std::string& vsFile, const std::string& fsFile,std::map<std::string,std::string> vars={});

     void bind(const glm::mat4 &matModelo);
     void bind(const glm::mat4 &matModelo,std::vector<glm::mat4> pose,std::vector<glm::mat4> bindPoses);
     void unbind();

     unsigned int id();
     glm::mat4 matProy;
     glm::mat4 matVista;
     glm::vec3 vecVista;

private:
	unsigned int shader_id;
	unsigned int shader_vp;
	unsigned int shader_fp;


	 int projectionMatrixLocation;
     int viewMatrixLocation;
     int modelMatrixLocation;
     int normalMatrixLocation;
     int poseMatrixLocation;
     int vecVistaLocation;
};

#endif
