#ifndef _REP_H_
#define _REP_H_
#include "render/Camara.h"
#include "render/Luz.h"
class Rep{
    public:
        virtual void dibujar(Camara& cam,Luz& l)=0;
        virtual void act(float dt)=0;
        Rep()=default;
        virtual ~Rep()=default;
};
#endif
