#include "RepMap.h"
#include <iostream>
#include "includeglm.h"
using namespace std;
using namespace glm;
RepMap::RepMap(Mapa& m)
:mapa(m)
{
     meshes.reserve(mapa.bloques.size());
     for(Bloque& b:mapa.bloques){
         if(b.borde){
             meshes.push_back(unique_ptr<Mesh>{new Mesh(MeshBloque::generar(mapa,b))});
         }
     }
     cout<<"Meshes: "<<meshes.size()<<" Bloques"<<mapa.bloques.size()<<endl;
}

RepMap::~RepMap()
{
}
void RepMap::dibujar(Camara& cam,Luz& l){
  sha->bind();
  sha->setmat4("projectionMatrix" ,cam.getMatProy());
  sha->setmat4("viewMatrix",cam.getMatVista()); 
  sha->setmat4("viewMatrixInv",inverse(cam.getMatVista()));
  sha->setmat4("modelMatrix",mat4(1.0f));
  sha->setmat4("normalMatrix",transpose(inverse(mat4(1.0f))));
  sha->setvec3("vecVista",cam.getOrientacion());
  sha->setvec3("luz",l.pos);
  for(auto& mesh:meshes){
      mesh->dibujar();
  }

}
