#ifndef REPRESENTACIONENTIDAD_H
#define REPRESENTACIONENTIDAD_H
#include "entidades/Entidad.h"
#include "render/Mesh.h"
#include "esqueleto/Esqueleto.h"
#include "esqueleto/Animador.h"
#include <memory>
class RepresentacionEntidad
{
     public:
          std::unique_ptr<Entidad> ent;
          std::unique_ptr<Mesh> mesh;
          std::unique_ptr<Esqueleto> esq;
          std::unique_ptr<Animador> ani;
          Shader* shader;
          Shader* shaderBorde;
          Shader* shaderSombra;
          RepresentacionEntidad();
          RepresentacionEntidad(const RepresentacionEntidad&)=delete;
          RepresentacionEntidad& operator=(const RepresentacionEntidad&) = delete;
          RepresentacionEntidad(RepresentacionEntidad&&)=default;
          RepresentacionEntidad& operator=(RepresentacionEntidad&&)=default;
     protected:
     private:
};

#endif // REPRESENTACIONENTIDAD_H
