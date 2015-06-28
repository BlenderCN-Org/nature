#ifndef REPSER_H
#define REPSER_H
#include "RepEnt.h"

#include "entidades/Ser.h"
class RepSer:public RepEnt{
    public:
        virtual void act(float dt);
        virtual void dibujar(Entidad* ent,Camara& cam,Luz&l);
};
#endif
