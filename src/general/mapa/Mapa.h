
#ifndef __Mapa_h_
#define __Mapa_h_
#include <vector>

#include "Bloque.h"
#include "Voxel.h"
#include "Cubo.h"
#include <iostream>
const int TAMANO_BLOQUE=32;
const float NIVEL_DETALLE=0.5;


//using MatrizBloques =std::array<std::array<Bloque,20>,20>;
class Mapa{


public:
   Mapa(int nbloqx,int nbloqy,int nbloqz,float tamCubo=1.0f); //Inicializa el mapa con el numero de bloques indicado por tamx,tamy,tamz
//   void generarMesh(Ogre::SceneManager* mSceneManager);
   bool enRango(int x,int y,int z);
   Voxel& getVoxel(int x,int y,int z);
   Cubo getCuboVoxel(int x,int y,int z);
   void setVoxel(int x,int y,int z,Voxel v);
   int getTamX();
   int getTamY();
   int getTamZ();
   float getTamCubo();
   int getBloquesX();
   int getBloquesY();
   int getBloquesZ();
   int getTamanoBloque();
   std::vector<Bloque> bloques;
   std::vector<glm::vec3> paleta;
   void detectarBordes();
   void resize(int nblox,int nbloqy,int nbloqz,float tamCubo=1.0f);
private:
   int nbloqx;
   int nbloqy;
   int nbloqz;
   int tamx;
   int tamy;
   int tamz;
   float tamCubo=1.0f;
   std::vector<Voxel> datos;



};


#endif
