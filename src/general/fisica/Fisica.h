#ifndef _Fisica_H_
#define _Fisica_H_
#include "entidades/Entidad.h"
#include "Colisionador.h"
class Fisica{
    public:
        /*metodos {{{*/
        void aplicar(Entidad& entidad,Mapa& mapa,float dt);
        /*}}}*/

    private:
       /*fuerzas {{{*/
        float gravedad=-9.8;
        Colisionador col;
        /*}}}*/
};




#endif
