#ifndef __Iluminador_h_
#define __Iluminador_h_
#include <vector>
#include "Mapa.h"
#include "includeglm.h"
class Iluminador{

public:
    void iluminar(Mapa *m,glm::vec3 vector);
    void iluminar(Mapa *m,int x,int y,int z,Voxel &v,glm::vec3 vector);
    void emitirSombra(Mapa *m,int x,int y,int z,Voxel &v,glm::vec3 vector);
};
#endif
