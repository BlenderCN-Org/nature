#ifndef MESHBLOQUE_H
#define MESHBLOQUE_H
#include "mapa/Bloque.h"
#include "mapa/Mapa.h"
#include "openglnat.h"
#include "Shader.h"
class MeshBloque
{
     public:
          MeshBloque(Mapa& m, Bloque& b);
          MeshBloque(const MeshBloque&)=delete;
          MeshBloque& operator=(const MeshBloque&) = delete;
          MeshBloque(MeshBloque&&)=default;
          MeshBloque& operator=(MeshBloque&&) = default;
          virtual ~MeshBloque();
          void dibujar(Shader* shader,const glm::mat4 &modelMatrix);
        void bindAtributtes();

     private:
         GLuint vao;
         GLuint vbo[4];
         int nvert;
         int ncaras;

};

#endif // MESHBLOQUE_H
