#ifndef JUEGO_H
#define JUEGO_H
#include "render/Shader.h"
#include "render/Mesh.h"
#include "entidades/Entidad.h"
#include "RepresentacionEntidad.h"
#include "RepresentacionMapa.h"
#include <vector>
#include <memory>
#include "control/ControlCamara.h"
#include "mapa/Mapa.h"
#include "render/Camara.h"
#include "util/Tiempo.h"
#include "fisica/Fisica.h"
#include "esqueleto/Esqueleto.h"
#include "render/MeshEsqueleto.h"

class Juego:public ControlCamara
{
     public:
          float dtf=0.02f; //Tiempo fijo para el calculo de las fisicas
          float tacumf=0.0f; //Tiempo fijo para el calculo de las fisicas
          std::vector<std::unique_ptr<Shader>> shaders;
          std::vector<RepresentacionEntidad>  rep{4};
          Juego();
          virtual ~Juego();
          void loop();
          void ejes(float x,float z);
          void teclaMovimiento(float x,float y,float z);
          void generarMapa();
     private:
          Mapa mapa;
          Fisica fisica;
          Camara camara;
          Tiempo t;
          float tanim=0.0f;
          std::unique_ptr<RepresentacionMapa> repMapa;
          std::unique_ptr<Esqueleto> esq;
          std::unique_ptr<MeshEsqueleto> esqMesh;
          std::unique_ptr<Mesh> cubo;
           
};

#endif // JUEGO_H