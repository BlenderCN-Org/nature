
#ifndef __Generador_h_
#define __Generador_h_

#include "Mapa.h"
#include <vector>
#include <queue>
#include <mutex>
#include "util/Imagen.h"
#include "render/MeshDatos.h"
class Generador{
public:
//      void static generar(Mapa *m,std::queue<Bloque> *cola, std::mutex* mt);
      void static generar(Mapa *m,std::queue<Bloque> *cola);

      void static generarPlanicieRocosa(Mapa *m,Bloque &b);
      void static generarPajaro(Mapa *m, Bloque &b);
      void static generarPerlin3d(Mapa *m, Bloque &b);
      void static generarImagen(Mapa *m,Bloque &b,Imagen& sup,Imagen& lat,Imagen& fre);
      void static generarVoxelizar(Mapa *m,MeshDatos& md,float tamCubo=1.0f);
      static std::vector<RGB> paleta;
};

#endif
