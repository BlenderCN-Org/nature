#ifndef _MESH_DATOS_H_
#define _MESH_DATOS_H_
#include <vector>
#include <string>
#include "openglnat.h"
#include "includeglm.h"
class MeshDatos{
    public:
        MeshDatos(std::string nombre);
        MeshDatos();
        static MeshDatos plano(float ancho,float alto);
        static MeshDatos linea(glm::vec3 v);
        void cargar(std::string nombre);
        std::vector<glm::vec3> vert;
        std::vector<glm::vec3> normal;
        std::vector<glm::vec3> color;
        std::vector<glm::vec4> oclusion;
        std::vector<float> peso;
        std::vector<float> hueso;
        std::vector<glm::vec2> uv;
        std::vector<glm::ivec3> caras;
};
#endif
