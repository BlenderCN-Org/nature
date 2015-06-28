#ifndef MESH_H
#define MESH_H

#include <string>
#include "util/Path.h"
#include "openglnat.h"
#include "Shader.h"
#include "MeshDatos.h"
enum class UsosVBO{vertices=0,normales,total};

class Mesh
{
    public:
        Mesh(MeshDatos d);
        Mesh(std::string path);
        Mesh(const Mesh&)=delete;
        Mesh& operator=(const Mesh&) = delete;
        Mesh(Mesh&&);
        Mesh& operator=(Mesh&&);
        virtual ~Mesh();
        void dibujar(Shader* shader,const glm::mat4 &modelMatrix,bool cullBack=true);
        void dibujar(bool cullBack=true);
        void dibujar(Shader* shader,const glm::mat4 &modelMatrix,std::vector<glm::mat4> pose,std::vector<glm::mat4> bindPoses,bool cullBack=true);
        void bindAtributtes();
    private:
        GLuint vao;
        std::vector<GLuint> vbo=std::vector<GLuint>(8,0);
        int nvert;
        int ncaras;
        bool usarVAO=true;


};

#endif // MESH_H
