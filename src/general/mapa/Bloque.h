
#ifndef __Bloque_h_
#define __Bloque_h_





class Bloque{

public:
      Bloque(int nx,int ny,int nz,int ntam);
      Bloque(){};
      bool borde;
      int x;
      int y;
      int z;
      int tam;
};

#endif
