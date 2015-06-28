#include "RepFactory.h"
#include "util/Path.h"
#include "render/Mesh.h"
#include "render/Shader.h"
using namespace std;
unique_ptr<RepSer> RepFactory::being(BeingType type){
    unique_ptr<RepSer> rep=unique_ptr<RepSer>(new RepSer());
/*    rep->mesh=unique_ptr<Mesh>(new Mesh(MeshDatos(Path::mesh("cubico"))));
//    rep->mesh=unique_ptr<Mesh>(new Mesh(Path::mesh("cubico")));
    rep->sha=unique_ptr<Shader>(new Shader(Path::shader("animado.vert"),Path::shader("basico.frag"),map<string,string>{{"%nhuesos%","6"}}));
        */
    switch(type){
        case BeingType::Turos:
            rep->mesh=MeshManager::instance()->load("turos",Path::mesh("turos"));
            rep->sha=ShaderManager::instance()->load("turos",Path::shader("animado.vert"),Path::shader("basico.frag"),map<string,string>{{"%nhuesos%","6"}});
            break;
        case BeingType::Human:
            rep->mesh=MeshManager::instance()->load("human",Path::mesh("cubico"));
            rep->sha=ShaderManager::instance()->load("human",Path::shader("animado.vert"),Path::shader("basico.frag"),map<string,string>{{"%nhuesos%","6"}});
            break;           
    }
    return rep;
};
