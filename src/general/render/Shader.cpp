#include "Shader.h"
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <utility>
#include "util/Path.h"


using namespace std;
using namespace glm;

std::string leerArchivo(const string& nombre) {
    cout<<"cargando shader:"<<nombre<<endl;
	std::ifstream f{nombre, std::ios::in };
    std::stringstream buffer;
    buffer << f.rdbuf();
    return buffer.str();
}

static void validateShader(GLuint shader, const char* file = 0) {
	const unsigned int BUFFER_SIZE = 512;
	char buffer[BUFFER_SIZE];
	memset(buffer, 0, BUFFER_SIZE);
	GLsizei length = 0;

	glGetShaderInfoLog(shader, BUFFER_SIZE, &length, buffer);
	if (length > 0) {
		cerr << "Shader " << shader << " (" << (file?file:"") << ") compile error: " << buffer << endl;
	}
}

static void validateProgram(GLuint program) {
	const unsigned int BUFFER_SIZE = 512;
	char buffer[BUFFER_SIZE];
	memset(buffer, 0, BUFFER_SIZE);
	GLsizei length = 0;

	memset(buffer, 0, BUFFER_SIZE);
	glGetProgramInfoLog(program, BUFFER_SIZE, &length, buffer);
	if (length > 0)
		cerr << "Program " << program << " link error: " << buffer << endl;

	glValidateProgram(program);
	GLint status;
	glGetProgramiv(program, GL_VALIDATE_STATUS, &status);
	if (status == GL_FALSE)
		cerr << "Error validating shader " << program << endl;
}

Shader::Shader(Shader&& n){
   cout<<"moviendo shader "<<shader_id<<endl;
   swap(shader_id,n.shader_id);
   swap(shader_vp,n.shader_vp);
   swap(shader_fp,n.shader_fp);
}
Shader& Shader::operator=(Shader&& n){
   cout<<"moviendo shader "<<shader_id<<endl;
   swap(shader_id,n.shader_id);
   swap(shader_vp,n.shader_vp);
   swap(shader_fp,n.shader_fp);
   return *this;

}
Shader::Shader() {

}

Shader::Shader(const std::string& vsFile,const  std::string& fsFile,map<string,string> vars) {
    init(vsFile, fsFile,vars);
}

void Shader::init(const std::string& vsFile, const std::string&  fsFile,map<string,string> vars) {
    cout<<"creando shader"<<endl;
	shader_vp = glCreateShader(GL_VERTEX_SHADER);
	shader_fp = glCreateShader(GL_FRAGMENT_SHADER);
	std::string vsText = leerArchivo(vsFile);
	std::string fsText = leerArchivo(fsFile);
    for(auto v:vars){
        int pos;
        while((pos=vsText.find(v.first))!=string::npos){
            vsText.replace(pos,v.first.length(),v.second);
        }
//        cout<<vsText<<endl;
    }
	//std::cout<<"archivo:"<<vsFile<<std::endl;
	//std::cout<<"-----"<<std::endl;
     //std::cout<<vsText<<std::endl;
     const char* vsChar=vsText.c_str();
     const char* fsChar=fsText.c_str();

	glShaderSource(shader_vp, 1, &vsChar, 0);
	glShaderSource(shader_fp, 1, &fsChar, 0);

	glCompileShader(shader_vp);
    cout<<"shader error: "<<glGetError()<<endl;
	validateShader(shader_vp, vsFile.c_str());


	glCompileShader(shader_fp);
	validateShader(shader_fp, fsFile.c_str());
	shader_id = glCreateProgram();
	glAttachShader(shader_id, shader_fp);
	glAttachShader(shader_id, shader_vp);
  

    glBindAttribLocation(shader_id,0,"in_Position");
    glBindAttribLocation(shader_id,1,"in_Color");
    glBindAttribLocation(shader_id,2,"in_Normal");
    glBindAttribLocation(shader_id,3,"in_idHueso");
    glBindAttribLocation(shader_id,4,"in_peso");
    glBindAttribLocation(shader_id,5,"in_uv");
    glBindAttribLocation(shader_id,6,"in_oclu");
	glLinkProgram(shader_id);
	validateProgram(shader_id);
	projectionMatrixLocation = glGetUniformLocation(shader_id, "projectionMatrix");
    viewMatrixLocation = glGetUniformLocation(shader_id, "viewMatrix"); 
    viewMatrixInvLocation = glGetUniformLocation(shader_id, "viewMatrixInv"); 
    modelMatrixLocation = glGetUniformLocation(shader_id, "modelMatrix"); 
    normalMatrixLocation = glGetUniformLocation(shader_id, "normalMatrix"); 
    poseMatrixLocation = glGetUniformLocation(shader_id, "poseMatrix");
    vecVistaLocation = glGetUniformLocation(shader_id, "vecVista");
    textureLocation = glGetUniformLocation(shader_id, "textura");
    luzLocation = glGetUniformLocation(shader_id, "luz");
    luzMatrixLocation = glGetUniformLocation(shader_id, "luzMatrix");
    shadowMapLocation = glGetUniformLocation(shader_id, "shadowMap");
}

Shader::~Shader() {
	glDetachShader(shader_id, shader_fp);
	if(shader_id>0) glDeleteProgram(shader_id);
    if(shader_fp>0) glDeleteShader(shader_fp);
    if(shader_vp>0) glDeleteShader(shader_vp);
}

unsigned int Shader::id() {
	return shader_id;
}
void Shader::bind() {
    if(shader_id>0){
        glUseProgram(shader_id);
    }
}
void Shader::bind(const glm::mat4 &matModelo) {
    //<F4>vec3 luz=vec3(0.0,-0.4,0.4);
    if(shader_id>0){
        glUseProgram(shader_id);
//        cout<<"Binded Shader"<<shader_id<<endl;
        glm::mat4 matNormal=glm::transpose(glm::inverse(matModelo));
        mat4 matVistaInv=inverse(matVista);
        glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &matProy[0][0]); 
        glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &matVista[0][0]); 
        glUniformMatrix4fv(viewMatrixInvLocation, 1, GL_FALSE, &matVistaInv[0][0]); 
        glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &matModelo[0][0]); 
        glUniformMatrix4fv(normalMatrixLocation, 1, GL_FALSE, &matNormal[0][0]);
        glUniformMatrix4fv(luzMatrixLocation, 1, GL_FALSE, &matLuz[0][0]);
        glUniform3fv(vecVistaLocation, 1, &vecVista[0]); 
        glUniform3fv(luzLocation, 1, &luz[0]); 
        if(tex!=nullptr&&usarTex){
            glActiveTexture(GL_TEXTURE0);
            tex->bind();
            glUniform1i(textureLocation, 0);
        }
    }
}
void Shader::bind(const glm::mat4 &matModelo,vector<glm::mat4> pose,vector<glm::mat4> bindPoses) {
    if(shader_id>0){
         bind(matModelo);
         std::vector<glm::vec3> colores(6);
         std::vector<glm::mat4> bindPosesInv;
         std::vector<glm::mat4> boneTransform;
         std::vector<glm::mat4> normalBone;
         for(int i=0;i<bindPoses.size();i++){
             glm::mat4 &bp= bindPoses[i];
             glm::mat4 &mp= pose[i];
             bindPosesInv.push_back(glm::inverse(bp));
             boneTransform.push_back(bp*mp*inverse(bp));
             normalBone.push_back(transpose(inverse(matModelo*bp*mp*inverse(bp))));
         }
         colores[0]=glm::vec3(1.0,0.0,0.0);
         colores[1]=glm::vec3(0.0,1.0,0.0);
         colores[2]=glm::vec3(0.0,0.0,1.0);
         colores[3]=glm::vec3(1.0,1.0,0.0);
         colores[4]=glm::vec3(1.0,0.0,1.0);
         colores[5]=glm::vec3(1.0,0.0,1.0);
         int coloresPos = glGetUniformLocation(shader_id, "colores"); 
         int bindPosesLocation = glGetUniformLocation(shader_id, "bindPose"); 
         int bindPosesInvLocation = glGetUniformLocation(shader_id, "bindPoseInv"); 
         int normalBoneLocation = glGetUniformLocation(shader_id, "normalBone"); 
         int boneTransformsLocation = glGetUniformLocation(shader_id, "boneTransforms"); 
         glUniformMatrix4fv(poseMatrixLocation, pose.size(), GL_FALSE, (float*)pose.data()); 
         glUniformMatrix4fv(bindPosesLocation, bindPoses.size(), GL_FALSE, (float*)bindPoses.data()); 
         glUniformMatrix4fv(bindPosesInvLocation, bindPosesInv.size(), GL_FALSE, (float*)bindPosesInv.data()); 
         glUniformMatrix4fv(boneTransformsLocation, boneTransform.size(), GL_FALSE, (float*)boneTransform.data()); 
         glUniformMatrix4fv(normalBoneLocation, normalBone.size(), GL_FALSE, (float*)normalBone.data()); 
         glUniform3fv(coloresPos, colores.size(),  (float*)colores.data()); 
    }
}
void Shader::unbind() {
	glUseProgram(0);
} 
int Shader::loc(string n){
    return  glGetUniformLocation(shader_id, n.c_str());
}

void Shader::setfloat(string n,float v){
    glUniform1f(loc(n),   v); 
}
void Shader::setfloat(string n,vector<float> &v){
    glUniform1fv(loc(n), v.size(), &v[0]); 
}
void Shader::setfloat(string n,int size,float* v){
    glUniform1fv(loc(n), size, v); 
}
/**vec2***/
void Shader::setvec2(string n,vec2 v){
    glUniform2fv(loc(n), 1,  &v[0]); 
}
void Shader::setvec2(string n,vector<vec2> &v){
    glUniform2fv(loc(n), v.size(),  &v[0][0]); 
}
void Shader::setvec2(string n,int size,float* v){
    glUniform2fv(loc(n), size, v); 
}
/**vec3***/
void Shader::setvec3(string n,vec3 v){
    glUniform3fv(loc(n), 1,  &v[0]); 

}
void Shader::setvec3(string n,vector<vec3> &v){
    glUniform3fv(loc(n), v.size(),  &v[0][0]); 
}
void Shader::setvec3(string n,int size,float* v){
    glUniform3fv(loc(n), size, v); 
}
/**vec4***/
void Shader::setvec4(string n,vec4 v){
    glUniform4fv(loc(n), 1,  &v[0]); 
}
void Shader::setvec4(string n,vector<vec4> &v){
    glUniform4fv(loc(n), v.size(),  &v[0][0]); 
}
void Shader::setvec4(string n,int size,float* v){
    glUniform4fv(loc(n), size, v); 
}
/***Mat3***/
void Shader::setmat3(string n,glm::mat3 v){
    glUniformMatrix3fv(loc(n), 1, GL_FALSE, &v[0][0]); 
}
void Shader::setmat3(string n,vector<glm::mat3> &v){
    glUniformMatrix3fv(loc(n), v.size(), GL_FALSE, &v[0][0][0]); 
}
void Shader::setmat3(string n,int size,float* v){
    glUniformMatrix3fv(loc(n), size, GL_FALSE,v); 
}
/***Mat4***/
void Shader::setmat4(string n,glm::mat4 v){
    glUniformMatrix4fv(loc(n), 1, GL_FALSE, &v[0][0]); 
}
void Shader::setmat4(string n,vector<glm::mat4> &v){
    glUniformMatrix4fv(loc(n), v.size(), GL_FALSE, &v[0][0][0]); 
}
void Shader::setmat4(string n,int size,float* v){
    glUniformMatrix4fv(loc(n), size, GL_FALSE,v); 
}
void Shader::settexture(string n,int i,Textura& t){
    glActiveTexture(GL_TEXTURE0+i);
    t.bind();
    glUniform1i(loc(n), i);
}

