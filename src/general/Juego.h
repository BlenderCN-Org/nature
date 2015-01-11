#ifndef JUEGO_H
#define JUEGO_H
#include "render/Shader.h"
#include "render/Mesh.h"
#include "entidades/Entidad.h"
#include "entidades/Personaje.h"
#include "RepresentacionEntidad.h"
#include "RepresentacionMapa.h"
#include <vector>
#include <memory>
#include "control/ControlCamara.h"
#include "mapa/Mapa.h"
#include "render/Camara.h"
#include "render/CamSegPaj.h"
#include "control/ControlJugador.h"
#include "util/Tiempo.h"
#include "fisica/Fisica.h"
#include "esqueleto/Esqueleto.h"
#include "render/MeshEsqueleto.h"
#include "render/ShadowMap.h"

class Juego:public ControlCamara,ControlJugador
{
     public:
          float dtf=0.02f; //Tiempo fijo para el calculo de las fisicas
          float tacumf=0.0f; //Tiempo fijo para el calculo de las fisicas
          std::vector<std::unique_ptr<Shader>> shaders;
          std::vector<RepresentacionEntidad>  rep;
          Juego();
          virtual ~Juego();
          void loop();
          /*control personaje*/
          void ejes(float x,float z);
          void movimiento(float x,float y,float z);
          void teclaPres(float x,float y,float z);
/*control personaje*/
          virtual void presionaSalto(); 
          virtual void sueltaSalto(); 
          virtual void ejeMovimiento(float x,float y); 
          void generarMapa();
     private:
          Mapa mapa;
          Fisica fisica;
          Camara camara;

          Tiempo t;
          float tanim=0.0f;
          ShadowMap shadowMap;
          std::unique_ptr<ControlCamara> ctrCam;
          std::unique_ptr<RepresentacionMapa> repMapa;
          std::unique_ptr<Esqueleto> esq;
          std::unique_ptr<MeshEsqueleto> esqMesh;
          std::unique_ptr<Mesh> cubo;
          glm::vec3 luz;
           
};

#endif // JUEGO_H
