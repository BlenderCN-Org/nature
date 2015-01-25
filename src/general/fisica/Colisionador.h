#ifndef _COLISIONADOR_H_
#define _COLISIONADOR_H_
#include "Colision.h"
#include "entidades/Entidad.h"
#include "Esfera.h"
#include "mapa/Mapa.h"
#include <vector>

class Colisionador{
    public:
        std::vector<Colision> revColision(Entidad& e,Mapa& m);
        static Colision revColision(Entidad& e1,Entidad& e2);
        static Colision revColision(Esfera& e1,Esfera& e2);
};


#endif
