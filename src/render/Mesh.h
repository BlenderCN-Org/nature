#ifndef MESH_H
#define MESH_H

#include <string>
#include "util/GestorRutas.h"
#include "openglnat.h"
#include "Shader.h"

enum class UsosVBO{vertices=0,normales,total};
class Mesh
{
    public:
        Mesh(std::string nombre);
        Mesh(const Mesh&)=delete;
        Mesh& operator=(const Mesh&) = delete;
        Mesh(Mesh&&)=default;
        Mesh& operator=(Mesh&&) = default;
        virtual ~Mesh();
        void dibujar(Shader* shader,const glm::mat4 &modelMatrix);
        void bindAtributtes();
    private:
        GLuint vao;
        GLuint vbo[4];
        int nvert;
        int ncaras;
        bool usarVAO=true;


};

#endif // MESH_H
