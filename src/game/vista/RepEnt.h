#ifndef _REPENT_H_
#define _REPENT_H_

#include "render/Mesh.h"
#include "esqueleto/Esqueleto.h"
#include "esqueleto/Animador.h"
#include "render/Camara.h"
#include "render/Luz.h"
#include "audio/AlSource.h"
#include "audio/AlBuffer.h"
#include "shaders/ShaBasic.h"
#include <memory>
#include "managers/Managers.h"

class Entidad;
class RepEnt{
    public:
        MeshManager::ResHanType mesh;
        ShaderManager::ResHanType sha;
        TextureManager::ResHanType tex;

//        std::unique_ptr<Mesh> mesh;
  //      std::unique_ptr<Shader> sha;
        virtual void dibujar(Entidad* ent,Camara& cam,Luz& l);
        virtual void act(float dt);
        RepEnt()=default;
        virtual  ~RepEnt()=default;
        RepEnt& operator=(const RepEnt&) = delete;
        RepEnt(RepEnt&&)=default;
        RepEnt& operator=(RepEnt&&)=default;
};
#endif


