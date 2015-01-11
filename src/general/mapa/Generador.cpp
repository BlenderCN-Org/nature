#include "Generador.h"
#include "noises/simplexnoise1234.h"
#include <random>
#include <iostream>
#include <functional>
#include <queue>
#include <mutex>
#include <thread>
#include <algorithm>
#include "util/Imagen.h"
#include "glm/gtx/intersect.hpp"
using namespace std;
using namespace glm;
vector<RGB> Generador::paleta=vector<RGB>();
void Generador::generar(Mapa *m,queue<Bloque> *cola, mutex* mt){
    // int i=0;
     
     bool vacia=false;
     Bloque  b;
     Imagen fre{"mapas/isla/frente.png"};
     Imagen lat{"mapas/isla/lateral.png"};
     Imagen sup{"mapas/isla/superior.png"};
    // std::chrono::milliseconds dura( 100 );
     do{
          mt->lock();
          if(!(vacia=cola->empty())){
              b=cola->front();
              cola->pop();
          }
          mt->unlock();
          if(!vacia)
//               generarPlanicieRocosa(m,b);
               generarImagen(m,b,sup,lat,fre);

     }while(!vacia);

}

void Generador::generar(Mapa *m,queue<Bloque> *cola){
    // int i=0;
     bool vacia=false;
     Bloque  b;
     //Imagen img("res/prueba.png");
     //cout<<"ancho x alto="<<img.ancho<<"x"<<img.alto<<endl;
     //for(int y=0;y<img.alto;y++){
         //for(int x=0;x<img.ancho;x++){
          //   RGB color=img.getPixel(x,y);
      //       cout<<"("<<(int)color.r<<","<<(int)color.g<<","<<(int)color.b<<") ";
       //  }
        // cout<<endl;
     //}
     //cout<<"-----"<<endl;

    // std::chrono::milliseconds dura( 100 );
     Imagen fre{"res/mapas/isla/frente.png"};
     Imagen lat{"res/mapas/isla/lateral.png"};
     Imagen sup{"res/mapas/isla/superior.png"};
     paleta.resize(0);
     paleta.push_back({0,0,0});
     do{
          if(!(vacia=cola->empty())){
              b=cola->front();
              cola->pop();
          }
          if(!vacia)
               generarPlanicieRocosa(m,b);
//               generarImagen(m,b,sup,lat,fre);

     }while(!vacia);
    for(RGB cpal:paleta){
        m->paleta.push_back(glm::vec3(((float)cpal.r)/255.0f,((float)cpal.g)/255.0f,((float)cpal.b)/255.0f));
    }

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

void Generador::generarImagen(Mapa *m,Bloque &b,Imagen& sup,Imagen& lat,Imagen& fre){

    RGB negro{0,0,0};
    RGB rojo{255,0,0};

    for(float y=b.y;y<b.y+b.tam;++y){
	    for(float x=b.x;x<b.x+b.tam;++x){
	       for(float z=b.z;z<b.z+b.tam;++z){

               RGB c=negro;
               RGB c1=sup.getPixel(x,y);
               RGB c2=fre.getPixel(y,z);
               RGB c3=lat.getPixel(x,z);

               if(c1!=negro){
                  if(c2!=negro){
                     if(c3!=negro){
                         if((lat.getPixel(x,z+1)==negro||fre.getPixel(y,z+1)==negro)
                            ){
                            c=c1;
                         }else
                         if((sup.getPixel(x-1,y)==negro||lat.getPixel(x-1,z)==negro)
                           ||(sup.getPixel(x+1,y)==negro||lat.getPixel(x+1,z)==negro)){
                            c=c2;
                         }else
                         if((sup.getPixel(x,y+1)==negro||fre.getPixel(y+1,z)==negro)
                           ||(sup.getPixel(x,y-1)==negro||fre.getPixel(y-1,z)==negro)
                           ||(lat.getPixel(x,z-1)==negro||fre.getPixel(y,z-1)==negro)){
                            c=c3;
                         }else{
                            c=rojo;
                         }
               //          c=rojo;
                     }
                  }
              }
              Voxel &v=m->getVoxel(x,y,z);
//              if(x==0||y==0||z==0){
  //                if(x==0) c=c2;    
    //              if(z==0) c=c1;    
      //            if(y==0) c=c3;    
    //
                  vector<RGB>::iterator it;
                  
                  if((it=find(paleta.begin(),paleta.end(),c))==paleta.end()){
                     paleta.push_back(c);
                     v.r=paleta.size()-1;
                  }else{
                     v.r=std::distance(paleta.begin(),it);
                  }
        //      }else
          //        v.r=0;

           }

        }
    }
//    m->paleta.reserve(paleta.size());

}
void Generador::generarPlanicieRocosa(Mapa *m,Bloque &b){
      float factor=0.006;
      RGB grama{104,148,104};
      RGB negro{0,0,0};
      RGB tierra{148,137,100};
      RGB c;
     vector<RGB>::iterator it;
	  std::default_random_engine generator;
	  std::uniform_real_distribution<float> dist(-0.2,0.2);
	  auto aleatorio = std::bind(dist,generator);
      for(float y=b.y;y<b.y+b.tam;++y){
	  for(float x=b.x;x<b.x+b.tam;++x){
          float pos=SimplexNoise1234::noise(x*factor*NIVEL_DETALLE,y*factor*NIVEL_DETALLE);
          pos=0.5+pos*0.5;
          float altura=m->getTamZ()*pos*0.2;
         // cout<<"altura="<<altura<<endl;
          for(float z=b.z;z<b.z+b.tam;++z){
               Voxel &v=m->getVoxel(x,y,z);
               c=negro;
               if(z<=altura){
                  c=grama; 
               }
         if((it=find(paleta.begin(),paleta.end(),c))==paleta.end()){
             paleta.push_back(c);
             v.r=paleta.size()-1;
         }else{
             v.r=std::distance(paleta.begin(),it);
         }




          }
	      if(pos>0.40){

		    float alturaNueva=(altura*2+pos*((float)m->getTamZ())/14*(pos+1.0));
		    float nx=x;
		    float ny=y;
		    for(int z=altura;z<alturaNueva&&z<b.z+b.tam;++z){
                   Voxel &v=m->getVoxel(x,y,z);
		         float zn=(float)((int)alturaNueva);
                   if(z>alturaNueva-1){
                      c=grama;
                   }else{
                      c=tierra;
                   }
                 if((it=find(paleta.begin(),paleta.end(),c))==paleta.end()){
                     paleta.push_back(c);
                     v.r=paleta.size()-1;
                 }else{
                     v.r=std::distance(paleta.begin(),it);
                 }


		    }

	     }
        }
    }

}


void Generador::generarVoxelizar(Mapa *m,MeshDatos& md,float tamCubo){
    vec3 pmin;
    vec3 pmax;
    m->paleta.clear();
    m->paleta.push_back(vec3(0,0,0));
    m->paleta.push_back(vec3(0.6,0.6,0.6));
    if(md.vert.size()>0){
        pmin=md.vert[0];
        pmax=md.vert[0];
    }
    for(vec3 v:md.vert){
       pmin.x=glm::min(pmin.x,v.x);
       pmin.y=glm::min(pmin.y,v.y);
       pmin.z=glm::min(pmin.z,v.z);
       pmax.x=glm::max(pmax.x,v.x);
       pmax.y=glm::max(pmax.y,v.y);
       pmax.z=glm::max(pmax.z,v.z);
    }

    pmin.x=floor(pmin.x);
    pmin.y=floor(pmin.y);
    pmin.z=floor(pmin.z);

    pmax.x=ceil(pmax.x/tamCubo);
    pmax.y=ceil(pmax.y/tamCubo);
    pmax.z=ceil(pmax.z/tamCubo);
    
    cout<<"min:("<<pmin.x<<","<<pmin.y<<","<<pmin.z<<");pmax:("<<pmax.x<<","<<pmax.y<<","<<pmax.z<<")"<<endl;
    int offx=1-pmin.x;
    int offy=1-pmin.y;
    int offz=1-pmin.z;
    m->resize(ceil((pmax.x-pmin.x+2)/TAMANO_BLOQUE),ceil((pmax.y-pmin.y+2)/TAMANO_BLOQUE),ceil((pmax.z-pmin.z+2)/TAMANO_BLOQUE),tamCubo);
    cout<<"tam("<<m->getTamX()<<","<<m->getTamY()<<","<<m->getTamZ()<<")"<<endl;
    for(int x=pmin.x;x<pmax.x;x++){
        for(int y=pmin.y;y<pmax.y;y++){
            for(int z=pmin.z;z<pmax.z;z++){
               int n=0;
               for(auto c:md.caras){
                   vec3 bary;
                   vec3 p=vec3(x*tamCubo,y*tamCubo,z*tamCubo);
                   if(intersectRayTriangle(p,vec3(0,0,-1),md.vert[c.x],md.vert[c.y],md.vert[c.z],bary)){
                          n++;
                   }else
                   if(intersectRayTriangle(p,vec3(0,0,-1),md.vert[c.x],md.vert[c.z],md.vert[c.y],bary)){
                          n++;
                   }
               }
               if (n%2!=0){
                  m->getVoxel(offx+x,offy+y,offz+z).r=1;
               }else{
                  m->getVoxel(offx+x,offy+y,offz+z).r=0;
               }

            }
        }
    }
    for(vec3& v:md.vert){
        v+=vec3(offx,offy,offz);
    }
}
