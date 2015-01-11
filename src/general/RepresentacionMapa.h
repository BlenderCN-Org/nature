#ifndef REPRESENTACIONMAPA_H
#define REPRESENTACIONMAPA_H
#include <vector>
#include "render/MeshBloque.h"
#include "render/Mesh.h"
#include <memory>

class RepresentacionMapa
{
     public:
          RepresentacionMapa(Mapa& m);
          virtual ~RepresentacionMapa();
          std::vector<std::unique_ptr<MeshBloque>> meshes;
          std::unique_ptr<Mesh> meshUnica;

     private:
          Mapa& mapa;


};

#endif // REPRESENTACIONMAPA_H
