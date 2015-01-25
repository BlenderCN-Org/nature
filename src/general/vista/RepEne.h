#ifndef _REPENE_H_
#define _REPENE_H_
#include "entidades/Personaje.h"
#include "entidades/Monstruo.h"
#include "RepEnt.h"

class RepEne:public RepEnt{
    public:
        virtual void act(float dt);
};
#endif
