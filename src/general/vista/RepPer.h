#ifndef _REPPER_H_
#define _REPPER_H_
#include "entidades/Personaje.h"
#include "RepEnt.h"


class RepPer:public RepEnt{
    public:
        virtual void act(float dt);

};
#endif
