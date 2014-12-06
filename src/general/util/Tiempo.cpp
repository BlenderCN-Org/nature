#include "Tiempo.h"
using namespace std;

Tiempo::Tiempo()
{
   tactual= chrono::system_clock::now();
   tviejo=tactual;
   tdelta= chrono::duration_cast<fsec>(tactual-tviejo);
}

Tiempo::~Tiempo()
{
     //dtor
}

void Tiempo::actualizar()
{
   tactual= chrono::system_clock::now();
   tdelta= chrono::duration_cast<fsec>(tactual-tviejo);
   tviejo=tactual;
}
