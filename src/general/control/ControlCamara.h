#ifndef CONTROLCAMARA_H
#define CONTROLCAMARA_H


class ControlCamara
{
     public:
          ControlCamara();
          virtual ~ControlCamara();
          virtual void act(float dt){};
          virtual void ejes(float x,float z){};
          virtual void zoom(float z){};
          virtual void movimiento(float x,float y,float z){};
     protected:
     private:
};

#endif // CONTROLCAMARA_H
