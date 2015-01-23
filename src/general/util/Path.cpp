#include "Path.h"

Path::Path()
{
    //ctor
}

Path::~Path()
{
    //dtor
}

std::string Path::base(){

    return "./res/";
}
 std::string Path::mesh(const std::string& nombreMesh){
    return base()+"/"+nombreMesh+".mesh";
}
std::string Path::res(const std::string& recurso){
    return base()+"/"+recurso;
}

std::string Path::shader(const std::string& nombreShader){
    return base()+"/shaders/"+nombreShader;
}
