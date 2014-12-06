#include "GestorRutas.h"

GestorRutas::GestorRutas()
{
    //ctor
}

GestorRutas::~GestorRutas()
{
    //dtor
}

std::string GestorRutas::getRutaDatos(){
    return "./res/";
}
 std::string GestorRutas::getRutaMesh(const std::string& nombreMesh){
    //return getRutaDatos()+"/modelos/"+nombreMesh+"/"+nombreMesh+".mesh";
    return getRutaDatos()+"/"+nombreMesh+".mesh";
}
std::string GestorRutas::getRutaShader(const std::string& nombreShader){
    //return getRutaDatos()+"/modelos/"+nombreMesh+"/"+nombreMesh+".mesh";
    return getRutaDatos()+"/shaders/"+nombreShader;
}
