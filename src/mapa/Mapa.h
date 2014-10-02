
#ifndef __Mapa_h_
#define __Mapa_h_
#include <vector>

#include "Bloque.h"
#include "Voxel.h"
#include <iostream>
const int TAMANO_BLOQUE=32;
const float NIVEL_DETALLE=0.5;


//using MatrizBloques =std::array<std::array<Bloque,20>,20>;
class Mapa{


public:
   Mapa(int nbloqx,int nbloqy,int nbloqz); //Inicializa el mapa con el numero de bloques indicado por tamx,tamy,tamz
//   void generarMesh(Ogre::SceneManager* mSceneManager);
   bool enRango(int x,int y,int z);
   Voxel& getVoxel(int x,int y,int z);
   void setVoxel(int x,int y,int z,Voxel v);
   int getTamX();
   int getTamY();
   int getTamZ();
   int getBloquesX();
   int getBloquesY();
   int getBloquesZ();
   int getTamanoBloque();
   std::vector<Bloque> bloques;
    void detectarBordes();
private:
   int nbloqx;
   int nbloqy;
   int nbloqz;
   int tamx;
   int tamy;
   int tamz;
   std::vector<Voxel> datos;



};


#endif
