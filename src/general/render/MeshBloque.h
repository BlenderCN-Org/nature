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
          MeshBloque(MeshBloque&&);
          MeshBloque& operator=(MeshBloque&&);
          virtual ~MeshBloque();
          void dibujar(Shader* shader,const glm::mat4 &modelMatrix,bool cullback=true);
          void vertex(Mapa& m,Bloque& b);
          void bindAtributtes();

     private:
         GLuint vao=0;
         std::vector<GLuint> vbo=std::vector<GLuint>(4,0);
         int nvert;
         int ncaras;

};

#endif // MESHBLOQUE_H
