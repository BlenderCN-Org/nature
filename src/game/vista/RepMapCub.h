#ifndef _REPMAPCUB_H_
#define _REPMAPCUB_H_
#include <vector>
#include "render/MeshBloque.h"
#include "render/Mesh.h"
#include "render/Shader.h"
#include "render/Luz.h"
#include "render/Camara.h"
#include "mapa/Mapa.h"
#include "managers/Managers.h"
#include <memory>

class RepMapCub
{
     public:
          RepMapCub(Mapa& m);
          virtual ~RepMapCub();

          ShaderManager::ResHanType sha;
          TextureManager::ResHanType tex;
          void dibujar(Camara& cam, Luz& l);
          void act(float dt){};
     private:
          Mapa& mapa;
          MeshManager::ResHanType meshCubo;

};
#endif
