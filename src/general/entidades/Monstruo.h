#ifndef _MONSTRUO_H_
#define _MONSTRUO_H_
#include "Entidad.h"
#include "Personaje.h"
#include "audio/AlSource.h"
#include "audio/AlBuffer.h"
using namespace glm;
class Monstruo:public Entidad{
    public:
        enum class Estado{
            Detenido,
            Encerrado,
            Caminando,
            AtaqueBomba,
            AtaqueGirar,
            Herido,
            Caido,
            Muerto
        };
        Estado estado=Estado::Encerrado;
        Personaje* p;
        float tiempoCaido;
        float tiempoDetenido;
        float tiempoHerido;
        float zBomba=0;
        virtual void act(float dt);
        virtual void colisiona(Colision c);
        void detener();
        void liberar();
        void herir();
        int vida=6;
        bool lateral=false;
        AlSource source;
        AlBuffer sngrunir1{"res/grunir1.wav"};
        AlBuffer snherido{"res/monsherido.wav"};
};
#endif
