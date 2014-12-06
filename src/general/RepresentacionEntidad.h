#ifndef REPRESENTACIONENTIDAD_H
#define REPRESENTACIONENTIDAD_H
#include "entidades/Entidad.h"
#include "render/Mesh.h"
#include <memory>
class RepresentacionEntidad
{
     public:
          Entidad entidad;
          std::unique_ptr<Mesh> mesh;
          RepresentacionEntidad();
          RepresentacionEntidad(RepresentacionEntidad && )=default;
          virtual ~RepresentacionEntidad();
     protected:
     private:
};

#endif // REPRESENTACIONENTIDAD_H
