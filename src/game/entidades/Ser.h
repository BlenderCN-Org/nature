#ifndef SER_H
#define SER_H
#include "esqueleto/Esqueleto.h"
#include "esqueleto/Animador.h"
#include "entidades/Entidad.h"
#include "entidades/Types.h"
class Ser:public Entidad{
    public:
        Ser(Esqueleto e,BeingType t=BeingType::Turos);
        float energia;//rango de valores: 0.0-1.0
        float salud;   //rango de valores: 0.0-1.0
        float rv;//rango de vision
        Esqueleto esq;
        Animador ani;
        BeingType type;

};
#endif 
