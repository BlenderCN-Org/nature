
#ifndef __Generador_h_
#define __Generador_h_

#include "Mapa.h"
#include <queue>
#include <mutex>
class Generador{
public:
      void static generar(Mapa *m,std::queue<Bloque> *cola, std::mutex* mt);
      void static generar(Mapa *m,std::queue<Bloque> *cola);

      void static generarPlanicieRocosa(Mapa *m,Bloque &b);
      void static generarPerlin3d(Bloque &bloque,int bx,int by);



};

#endif
