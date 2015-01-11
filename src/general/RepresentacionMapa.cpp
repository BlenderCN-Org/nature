#include "RepresentacionMapa.h"
#include "mapa/Bloque.h"
using namespace std;
RepresentacionMapa::RepresentacionMapa(Mapa& m)
:mapa(m)
{
     meshes.reserve(mapa.bloques.size());

     for(Bloque& b:mapa.bloques){
         if(b.borde){
             meshes.push_back(unique_ptr<MeshBloque>{new MeshBloque(mapa,b)});
         }
     }
     cout<<"Meshes: "<<meshes.size()<<" Bloques"<<mapa.bloques.size()<<endl;
}

RepresentacionMapa::~RepresentacionMapa()
{
     //dtor
}
