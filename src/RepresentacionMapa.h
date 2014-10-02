#ifndef REPRESENTACIONMAPA_H
#define REPRESENTACIONMAPA_H
#include <vector>
#include "render/MeshBloque.h"
#include <memory>

class RepresentacionMapa
{
     public:
          RepresentacionMapa(Mapa& m);
          virtual ~RepresentacionMapa();
          std::vector<std::unique_ptr<MeshBloque>> meshes;

     private:
          Mapa& mapa;


};

#endif // REPRESENTACIONMAPA_H
