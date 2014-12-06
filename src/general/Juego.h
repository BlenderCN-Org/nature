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
class Juego:public ControlCamara
{
     public:
          std::vector<std::unique_ptr<Shader>> shaders;
          std::vector<RepresentacionEntidad>  rep{2};
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
          std::unique_ptr<RepresentacionMapa> repMapa;
};

#endif // JUEGO_H
