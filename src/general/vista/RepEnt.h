#ifndef _REPENT_H_
#define _REPENT_H_
#include "Rep.h"
#include "entidades/Entidad.h"
#include "render/Mesh.h"
#include "esqueleto/Esqueleto.h"
#include "esqueleto/Animador.h"
#include "render/Camara.h"
#include "render/Luz.h"
#include "audio/AlSource.h"
#include "audio/AlBuffer.h"
#include <memory>
class RepEnt:public Rep{
    public:
        std::unique_ptr<Entidad> ent;
        std::shared_ptr<Mesh> mesh;
        std::unique_ptr<Esqueleto> esq;
        std::unique_ptr<Animador> ani;
        std::unique_ptr<Shader> sha;

        virtual void dibujar(Camara& cam,Luz& l);
        virtual void act(float dt);
        RepEnt()=default;
        virtual  ~RepEnt()=default;
        RepEnt& operator=(const RepEnt&) = delete;
        RepEnt(RepEnt&&)=default;
        RepEnt& operator=(RepEnt&&)=default;
};
#endif


