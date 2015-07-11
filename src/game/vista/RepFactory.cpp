#include "RepFactory.h"
#include "util/Path.h"
#include "render/Mesh.h"
#include "render/Shader.h"
using namespace std;
unique_ptr<RepSer> RepFactory::being(BeingType type){
    unique_ptr<RepSer> rep=unique_ptr<RepSer>(new RepSer());
    switch(type){
        case BeingType::Turos:
            rep->mesh=MeshManager::instance()->load("turos",Path::mesh("turos"));
            rep->sha=ShaderManager::instance()->load("turos",Path::shader("animado.vert"),Path::shader("textura.frag"),map<string,string>{{"%nhuesos%","6"}});
            rep->tex=TextureManager::instance()->load("turos",Path::res("turos.png"));
            break;
        case BeingType::Human:
            rep->mesh=MeshManager::instance()->load("human",Path::mesh("cubico"));
            rep->sha=ShaderManager::instance()->load("human",Path::shader("animado.vert"),Path::shader("textura.frag"),map<string,string>{{"%nhuesos%","6"}});
            rep->tex=TextureManager::instance()->load("human",Path::res("cubico.png"));
            break;           
    }
    return rep;
};

unique_ptr<RepMapCub> RepFactory::mapa(Mapa& m){
    unique_ptr<RepMapCub> rep=unique_ptr<RepMapCub>(new RepMapCub(m));
    rep->sha=ShaderManager::instance()->load("mapa",Path::shader("basico.vert"),Path::shader("textura.frag"));
    rep->tex=TextureManager::instance()->load("mapa",Path::res("cubo.png"));
    return rep;
}
