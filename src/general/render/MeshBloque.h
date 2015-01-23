#ifndef MESHBLOQUE_H
#define MESHBLOQUE_H
#include "mapa/Bloque.h"
#include "mapa/Mapa.h"
#include "openglnat.h"
#include "Shader.h"
#include "MeshDatos.h"
class MeshBloque
{
     public:
           static MeshDatos generar(Mapa& m, Bloque& b);

};

#endif // MESHBLOQUE_H
