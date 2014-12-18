#ifndef _MESH_ESQUELETO_H_
#define _MESH_ESQUELETO_H_
#include "esqueleto/Esqueleto.h"
#include "openglnat.h"
#include "Shader.h"
#include <vector>

class MeshEsqueleto{
    public:
        MeshEsqueleto(Esqueleto& e);
        ~MeshEsqueleto();
        MeshEsqueleto(const MeshEsqueleto&)=delete;
        MeshEsqueleto& operator=(const MeshEsqueleto&) = delete;
        MeshEsqueleto(MeshEsqueleto&&)=default;
        MeshEsqueleto& operator=(MeshEsqueleto&&) = default;
        
        void bindAtributos();
        void dibujar(Shader* shader,const glm::mat4 &modelMatrix,std::vector<glm::mat4> pose,std::vector<glm::mat4> bindPoses);
        
    private:
        GLuint vao;
        GLuint vbo[4];
        int nhuesos;
};
#endif

