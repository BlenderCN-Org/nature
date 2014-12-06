#ifndef CONTROLCAMARA_H
#define CONTROLCAMARA_H


class ControlCamara
{
     public:
          ControlCamara();
          virtual ~ControlCamara();
          virtual void ejes(float x,float z){};
          virtual void teclaMovimiento(float x,float y,float z){};
     protected:
     private:
};

#endif // CONTROLCAMARA_H
