#ifndef _CUADRO_ESQUELETO_H_
#define _CUADRO_ESQUELETO_H_
#include <vector>
#include "CuadroHueso.h"
class CuadroEsqueleto{
    public:
        float tiempo;
        std::vector<CuadroHueso> huesos;
};
#endif 
