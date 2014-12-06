#ifndef _COLISIONADOR_H_
#define _COLISIONADOR_H_
#include "Colision.h"
#include "entidades/Entidad.h"
#include "mapa/Mapa.h"

class Colisionador{
    public:
        Colision revColision(Entidad e,Mapa m);
        

};


#endif
