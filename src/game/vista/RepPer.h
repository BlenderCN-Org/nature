#ifndef REPPER_H
#define REPPER_H
#include "RepSer.h"
#include "entidades/Ser.h"
#include "entidades/Personaje.h"
class RepPer:public RepSer{
    public:
        virtual void dibujar(Entidad* ent,Camara& cam,Luz&l);
        ShaderManager::ResHanType shaArma;
        MeshManager::ResHanType   meshArma;

};
#endif
