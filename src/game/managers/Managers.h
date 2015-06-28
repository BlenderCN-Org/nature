#ifndef _NATURE_MANAGERS_H_
#define _NATURE_MANAGERS_H_
#include "resources/Manager.h"
#include "render/Textura.h"
#include "render/Shader.h"
#include "render/Mesh.h"
    class TextureManager:public Manager<TextureManager,std::string,Textura>{
    };
    class ShaderManager:public Manager<ShaderManager,std::string,Shader>{
    };
    class MeshManager:public Manager<MeshManager,std::string,Mesh>{
    };
#endif
