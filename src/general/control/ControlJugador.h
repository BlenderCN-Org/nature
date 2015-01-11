#ifndef _CONTROL_JUGADOR_H_
#define _CONTROL_JUGADOR_H_
class ControlJugador{
    public:
        virtual void presionaSalto(){}; 
        virtual void sueltaSalto(){}; 
        virtual void ejeMovimiento(float x,float y){}; 
};
#endif
