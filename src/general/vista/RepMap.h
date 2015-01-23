#ifndef _REPMAP_H_
#define _REPMAP_H_
#include <vector>
#include "render/MeshBloque.h"
#include "render/Mesh.h"
#include "RepEnt.h"
#include "render/Shader.h"
#include "render/Camara.h"
#include "mapa/Mapa.h"
#include <memory>

class RepMap: public Rep
{
     public:
          RepMap(Mapa& m);
          virtual ~RepMap();
          std::vector<std::unique_ptr<Mesh>> meshes;
          std::unique_ptr<Mesh> meshUnica;
          std::unique_ptr<Shader> sha;
          void dibujar(Camara& cam, Luz& l);
          void act(float dt){};
     private:
          Mapa& mapa;


};
#endif
