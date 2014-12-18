#ifndef REPRESENTACIONENTIDAD_H
#define REPRESENTACIONENTIDAD_H
#include "entidades/Entidad.h"
#include "render/Mesh.h"
#include "esqueleto/Esqueleto.h"
#include <memory>
class RepresentacionEntidad
{
     public:
          Entidad entidad;
          std::unique_ptr<Mesh> mesh;
          std::unique_ptr<Esqueleto> esq;
          Shader* shader;
          Shader* shaderBorde;
          RepresentacionEntidad();
          RepresentacionEntidad(RepresentacionEntidad && )=default;
          virtual ~RepresentacionEntidad();
     protected:
     private:
};

#endif // REPRESENTACIONENTIDAD_H
