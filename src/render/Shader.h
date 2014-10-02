#ifndef __SHADER_H
#define __SHADER_H

#include <string>
#include "openglnat.h"
#include "includeglm.h"

class Shader {
public:
     Shader();
     Shader(const std::string& vsFile,const std::string& fsFile);
     ~Shader();

     void init(const std::string& vsFile, const std::string& fsFile);

     void bind(const glm::mat4 &matModelo);
     void unbind();

     unsigned int id();
     glm::mat4 matProy;
     glm::mat4 matVista;
private:
	unsigned int shader_id;
	unsigned int shader_vp;
	unsigned int shader_fp;


	int projectionMatrixLocation;
     int viewMatrixLocation;
     int modelMatrixLocation;
     int normalMatrixLocation;
};

#endif
