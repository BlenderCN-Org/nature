#ifndef _Fisica_H_
#define _Fisica_H_
#include "entidades/Entidad.h"
class Fisica{
    public:
        /*metodos {{{*/
        void aplicar(Entidad& entidad,float dt);
        /*}}}*/

    private:
       /*fuerzas {{{*/
        float gravedad=-9.8;
        /*}}}*/
};




#endif
