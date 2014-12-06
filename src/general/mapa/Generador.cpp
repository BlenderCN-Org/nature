#include "Generador.h"
#include "noises/simplexnoise1234.h"
#include <random>
#include <iostream>
#include <functional>
#include <queue>
#include <mutex>
#include <thread>
using namespace std;
void Generador::generar(Mapa *m,queue<Bloque> *cola, mutex* mt){
    // int i=0;
     bool vacia=false;
     Bloque  b;
    // std::chrono::milliseconds dura( 100 );
     do{
          mt->lock();
          if(!(vacia=cola->empty())){
              b=cola->front();
              cola->pop();
          }
          mt->unlock();
          if(!vacia)
               generarPlanicieRocosa(m,b);

     }while(!vacia);

}

void Generador::generar(Mapa *m,queue<Bloque> *cola){
    // int i=0;
     bool vacia=false;
     Bloque  b;
    // std::chrono::milliseconds dura( 100 );
     do{
          if(!(vacia=cola->empty())){
              b=cola->front();
              cola->pop();
          }
          if(!vacia)
               generarPlanicieRocosa(m,b);

     }while(!vacia);

}


void Generador::generarPerlin3d(Bloque &bloque,int bx,int by){
/*          for(float y=0;y<TAMANO_BLOQUE_HOR ;++y){
	     for(float x=0;x<TAMANO_BLOQUE_HOR;++x){
	        for(float z=0;z<TAMANO_BLOQUE_VER;++z){
             float pos=SimplexNoise1234::noise((bx*TAMANO_BLOQUE_HOR+x)*0.02,(by*TAMANO_BLOQUE_HOR+y)*0.02,z*0.02);
	        // float poscirle=SimplexNoise1234::noise((bx*TAMANO_BLOQUE_HOR+x)*1.5,(by*TAMANO_BLOQUE_HOR+y)*1.5);
                 //float altura=(int)(TAMANO_BLOQUE_VER/16*(pos+1.0));
                // char nombre[300];
	         bloque.data[(int)x][(int)y][(int)z].valor=1.0-pos;

		bloque.data[(int)x][(int)y][(int)z].r=0.3*z/TAMANO_BLOQUE_VER;
	        bloque.data[(int)x][(int)y][(int)z].g=0.6*z/TAMANO_BLOQUE_VER;
	        bloque.data[(int)x][(int)y][(int)z].b=0.3*z/TAMANO_BLOQUE_VER;
	        bloque.data[(int)x][(int)y][(int)z].a=1.0;

	       }

	    }
         }*/

}
void Generador::generarPlanicieRocosa(Mapa *m,Bloque &b){
       float factor=0.001;
	  std::default_random_engine generator;
	  std::uniform_real_distribution<float> dist(-0.2,0.2);
	  auto aleatorio = std::bind(dist,generator);
       for(float y=b.y;y<b.y+b.tam;++y){
	  for(float x=b.x;x<b.x+b.tam;++x){
          float pos=SimplexNoise1234::noise(x*factor*NIVEL_DETALLE,y*factor*NIVEL_DETALLE);
          float altura=m->getTamZ()*pos*0.2;
         // cout<<"altura="<<altura<<endl;
          for(float z=b.z;z<b.z+b.tam;++z){
               Voxel &v=m->getVoxel(x,y,z);
               if(z<=altura){
                   v.solido=true;
               }else{
                   v.solido=false;
               }
                v.r=0.1*255.0f;v.g=0.25* 255.0f;v.b=0.1*255.0f;v.a=1.0*255.0f;


          }
	      if(pos>0.40){

		    float alturaNueva=(altura*2+pos*((float)m->getTamZ())/14*(pos+1.0));
		    float nx=x;
		    float ny=y;

		    for(int z=altura;z<alturaNueva&&z<b.z+b.tam;++z){
                   Voxel &v=m->getVoxel(x,y,z);
		         float zn=(float)((int)alturaNueva);
		         v.solido=true;



//			 std::cout<<"zn"<<zn<<","<<((float)z)/zn*alturaNueva<<std::endl;
                   if(z>alturaNueva-3){
                      v.r=0.1*255.0f;v.g=0.25*255.0f;v.b=0.1*255.0f;v.a=1.0*255.0f;
                   }else{
                      v.r=0.42*255.0f;v.g=0.36*255.0f;v.b=0.24*255.0f;v.a=1.0*255.0f;
                   }
		    }

	     }
        }
    }

}
