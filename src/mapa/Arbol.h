#ifndef __ARBOL_H__
#define __ARBOL_H__

#include "Rama.h"



class Arbol{
public:
  float x=0;
  float y=0;
  float z=0;
  float reduccion=0.5;
  Rama raiz;
  void generarRama(float ox,float oy,float oz,float fx,float fy,float fz,float fac);
  void generarHoja(float fx,float fy,float fz,float fac);
  void generar();
  void generarMesh(Rama r,float x,float y,float z,float fac);

};




#endif
