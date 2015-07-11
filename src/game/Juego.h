#ifndef JUEGO_H
#define JUEGO_H
#include "render/Shader.h"
#include "render/Mesh.h"
#include "entidades/Entidad.h"
#include "entidades/Personaje.h"
#include "entidades/Monstruo.h"
#include "vista/RepEnt.h"
#include "vista/RepMap.h"
#include "vista/RepMapCub.h"
#include <vector>
#include <memory>
#include "control/ControlCamara.h"
#include "mapa/Mapa.h"
#include "render/Camara.h"
#include "render/Luz.h"
#include "render/CamSegPaj.h"
#include "control/ControlJugador.h"
#include "util/Tiempo.h"
#include "fisica/Fisica.h"
#include "esqueleto/Esqueleto.h"
#include "render/MeshEsqueleto.h"
#include "render/ShadowMap.h"
#include "audio/AlSource.h"
#include "audio/AlBuffer.h"
#include "audio/OggBuffer.h"
#include "audio/AlListener.h"
#include "control/SDLInput.h"
class Juego:public ControlCamara,ControlJugador
{
     public:
          float dtf=0.02f; //Tiempo fijo para el calculo de las fisicas
          float tacumf=0.0f; //Tiempo fijo para el calculo de las fisicas
          std::vector<std::unique_ptr<Entidad>>  ent;
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
          virtual void atacar(); 
          virtual void esquivar(); 
          virtual void ejeMovimiento(float x,float y); 
          void generarMapa();
          void render();
          std::vector<Esfera> getEsferas(Hueso& h);
          void colisionPersonajes();
          void tomarEspada();

     private:
          Mapa mapa;
          SDLInput input;
          Fisica fisica;
          Camara camara;

          Tiempo t;
          float tanim=0.0f;
          std::unique_ptr<ControlCamara> ctrCam;
          std::unique_ptr<RepMapCub> repMapa;
         // std::unique_ptr<RepMapCub> repMapa;
          Luz luz;
          glm::mat4 matLuz;
          AlListener listener;
          AlSource source;
          AlBuffer buffer;
          bool primerEje=true;
           
};

#endif // JUEGO_H
