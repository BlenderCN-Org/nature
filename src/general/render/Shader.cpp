#include "Shader.h"
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include "util/GestorRutas.h"


using namespace std;

std::string leerArchivo(const string& nombre) {
    cout<<"cargando shader:"<<nombre<<endl;
	std::ifstream f{nombre, std::ios::in };
    std::stringstream buffer;
    buffer << f.rdbuf();
    cout<<"shader content"<<buffer.str()<<endl;
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

Shader::Shader() {

}

Shader::Shader(const std::string& vsFile,const  std::string& fsFile) {
    init(vsFile, fsFile);
}

void Shader::init(const std::string& vsFile, const std::string&  fsFile) {
    cout<<"creando shader"<<endl;
	shader_vp = glCreateShader(GL_VERTEX_SHADER);
	shader_fp = glCreateShader(GL_FRAGMENT_SHADER);
	std::string vsText = leerArchivo(vsFile);
	std::string fsText = leerArchivo(fsFile);
	std::cout<<"archivo:"<<vsFile<<std::endl;
	std::cout<<"-----"<<std::endl;
     std::cout<<vsText<<std::endl;
     const char* vsChar=vsText.c_str();
     const char* fsChar=fsText.c_str();

	glShaderSource(shader_vp, 1, &vsChar, 0);
	glShaderSource(shader_fp, 1, &fsChar, 0);

	glCompileShader(shader_vp);
	validateShader(shader_vp, vsFile.c_str());
	glCompileShader(shader_fp);
	validateShader(shader_fp, fsFile.c_str());

	shader_id = glCreateProgram();
	glAttachShader(shader_id, shader_fp);
	glAttachShader(shader_id, shader_vp);
	glLinkProgram(shader_id);
	validateProgram(shader_id);
	projectionMatrixLocation = glGetUniformLocation(shader_id, "projectionMatrix"); // Get the location of our projection matrix in the shader
     viewMatrixLocation = glGetUniformLocation(shader_id, "viewMatrix"); // Get the location of our view matrix in the shader
     modelMatrixLocation = glGetUniformLocation(shader_id, "modelMatrix"); // Get the location of our model matrix in the shader
     normalMatrixLocation = glGetUniformLocation(shader_id, "normalMatrix"); // Get the location of our model matrix in the shader
    // std::cout<<projectionMatrixLocation<<","<<viewMatrixLocation<<","<<modelMatrixLocation<<","<<normalMatrixLocation<<std::endl;
}

Shader::~Shader() {
	glDetachShader(shader_id, shader_fp);
	glDetachShader(shader_id, shader_vp);

	glDeleteShader(shader_fp);
	glDeleteShader(shader_vp);
	glDeleteProgram(shader_id);


}

unsigned int Shader::id() {
	return shader_id;
}

void Shader::bind(const glm::mat4 &matModelo) {
	glUseProgram(shader_id);
    glm::mat4 matNormal=glm::transpose(glm::inverse(matVista*matModelo));
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &matProy[0][0]); // Send our projection matrix to the shader
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &matVista[0][0]); // Send our view matrix to the shader
    glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &matModelo[0][0]); // Send our model matrix to the shader
    glUniformMatrix4fv(normalMatrixLocation, 1, GL_FALSE, &matNormal[0][0]); // Send our model matrix to the shader
}

void Shader::unbind() {
	glUseProgram(0);
}
