#ifndef _ANIMACION_ESQUELETO_H_
#define _ANIMACION_ESQUELETO_H_
#include "includeglm.h"
#include "CuadroHueso.h"
#include "CuadroEsqueleto.h"
#include <string>
class AnimEsqueleto{
    public:
        std::string nombre;
        std::vector<CuadroEsqueleto> cuadros;

};

#endif
