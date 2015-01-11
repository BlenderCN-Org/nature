#ifndef _COLISIONADOR_H_
#define _COLISIONADOR_H_
#include "Colision.h"
#include "entidades/Entidad.h"
#include "mapa/Mapa.h"
#include <vector>

class Colisionador{
    public:
        std::vector<Colision> revColision(Entidad& e,Mapa& m);
        

};


#endif
