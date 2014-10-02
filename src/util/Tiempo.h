#ifndef TIEMPO_H
#define TIEMPO_H
#include <chrono>
typedef std::chrono::duration<float> fsec;
typedef std::chrono::time_point<std::chrono::system_clock> tiempo;
class Tiempo
{
     public:
          Tiempo();
          virtual ~Tiempo();
          void actualizar();
          float delta(){return tdelta.count();};
     private:
     tiempo tactual;
     tiempo tviejo;
     fsec tdelta;

};

#endif // TIEMPO_H
