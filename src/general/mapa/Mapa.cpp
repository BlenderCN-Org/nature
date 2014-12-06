#include "Mapa.h"
#include "Iluminador.h"
#include "time.h"
#include "noises/simplexnoise1234.h"
#include "Arbol.h"
#include "GeneradorArbol.h"
#include <random>
#include <vector>
using namespace std;
Mapa::Mapa(int bloqx,int bloqy,int bloqz,float tamCubo):
     nbloqx{bloqx},
     nbloqy{bloqy},
     nbloqz{bloqz},
     tamx{bloqx*TAMANO_BLOQUE},
     tamy{bloqy*TAMANO_BLOQUE},
     tamz{bloqz*TAMANO_BLOQUE},
     tamCubo{tamCubo},
     datos{static_cast<vector<Voxel>::size_type>( tamx*tamy*tamz),Voxel{}}
{
     for(int bz=0;bz<bloqz;++bz){
          for(int by=0;by<bloqy;++by){
               for(int bx=0;bx<bloqx;++bx){
                    this->bloques.emplace_back(bx*TAMANO_BLOQUE,by*TAMANO_BLOQUE,bz*TAMANO_BLOQUE,TAMANO_BLOQUE);
               }
          }
     }

}

float Mapa::getTamCubo(){
     return tamCubo;
}

int Mapa::getTamX(){
     return tamx;
}
int Mapa::getTamY(){
     return tamy;
}
int Mapa::getTamZ(){
     return tamz;
}
int Mapa::getBloquesX(){
     return  nbloqx;
}
int Mapa::getBloquesY(){
     return  nbloqy;
}
int Mapa::getBloquesZ(){
     return  nbloqz;
}
int getTamanoBloque(){
     return TAMANO_BLOQUE;
}
bool Mapa::enRango(int x,int y,int z){
    return x>=0&&x<tamx&&y>=0&&y<tamy&&z>=0&&z<tamz;
}
Voxel& Mapa::getVoxel(int x,int y,int z){
    return datos[tamy*tamx*z+y*tamx+x];
}
Cubo Mapa::getCuboVoxel(int x,int y,int z){
    Cubo c{glm::vec3(x-tamCubo/2,y-tamCubo/2,z-tamCubo/2),glm::vec3(tamCubo,tamCubo,tamCubo)};

    return c;
}

void Mapa::setVoxel(int x,int y,int z,Voxel v){
cout<<"acediendo a:"<<x<<","<<y<<","<<z<<endl;
  datos[tamy*tamx*z+y*tamx+x]=v;
}



void Mapa::detectarBordes(){
   int total=0;
   for(Bloque& b:bloques){
        int cont=0;
        for(int x=b.x;x<b.x+b.tam;x++){
           for(int y=b.y;y<b.y+b.tam;y++){
                for(int z=b.z;z<b.z+b.tam;z++){
                Voxel& v=getVoxel(x,y,z);
                    if(v.solido){
                        if((enRango(x-1,y,z)&&!(getVoxel(x-1,y,z).solido))
                            ||(enRango(x+1,y,z)&&!(getVoxel(x+1,y,z).solido))
                            ||(enRango(x,y-1,z)&&!(getVoxel(x,y-1,z).solido))
                            ||(enRango(x,y+1,z)&&!(getVoxel(x,y+1,z).solido))
                            ||(enRango(x,y,z-1)&&!(getVoxel(x,y,z-1).solido))
                            ||(enRango(x,y,z+1)&&!(getVoxel(x,y,z+1).solido))){
                                 v.borde=true;
                                 ++cont;
                       }
                    }
               }
           }
        }
        b.borde=cont>0;
        total+=cont;
   }
   cout <<"Total bordes="<<total<<endl;

}
