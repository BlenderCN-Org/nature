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
#include <cfloat>
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
               generarPerlin3d(m,b);
//               generarImagen(m,b,sup,lat,fre);

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
               //generarPlanicieRocosa(m,b);
               generarPerlin3d(m,b);
//               generarImagen(m,b,sup,lat,fre);

     }while(!vacia);
    for(RGB cpal:paleta){
        m->paleta.push_back(glm::vec3(((float)cpal.r)/255.0f,((float)cpal.g)/255.0f,((float)cpal.b)/255.0f));
    }

}


void Generador::generarPerlin3d(Mapa *m, Bloque &b){
      RGB grama{104,148,104};
      RGB negro{0,0,0};
      RGB tierra{148,137,100};
      RGB c=grama;
      for(float y=b.y;y<b.y+b.tam;++y){
	     for(float x=b.x;x<b.x+b.tam;++x){

               float pos=SimplexNoise1234::noise(x*0.0008,y*0.0008);
               pos=(pos+1.0f)/2.0f;
               int altura=1+pos*(m->getTamZ()-1);
               int alturaMax=m->getTamZ();
               vector<RGB>::iterator it;
	           for(float z=b.z;z<b.z+b.tam;++z){
                 float den=SimplexNoise1234::noise(x*0.003,y*0.003,z*0.003);
                 if(z<=altura&&(z<alturaMax*0.1||den>=0)){
                    Voxel& v=m->getVoxel(x,y,z);
                    if(z>=altura-2){
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
                         }
                     }
                  }
              }
              Voxel &v=m->getVoxel(x,y,z);
                  vector<RGB>::iterator it;
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
    paleta.clear();
    paleta.push_back(RGB{0,0,0});
    paleta.push_back(RGB{140,140,140});
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

    pmin.x=floor(pmin.x/tamCubo);
    pmin.y=floor(pmin.y/tamCubo);
    pmin.z=floor(pmin.z/tamCubo);

    pmax.x=ceil(pmax.x/tamCubo);
    pmax.y=ceil(pmax.y/tamCubo);
    pmax.z=ceil(pmax.z/tamCubo);
    
    cout<<"min:("<<pmin.x<<","<<pmin.y<<","<<pmin.z<<");pmax:("<<pmax.x<<","<<pmax.y<<","<<pmax.z<<")"<<endl;
    int offx=1-pmin.x;
    int offy=1-pmin.y;
    int offz=1-pmin.z;
    for(vec3& v:md.vert){
        v+=vec3(offx,offy,offz);
    }
    m->resize(ceil((pmax.x-pmin.x+2)/TAMANO_BLOQUE),ceil((pmax.y-pmin.y+2)/TAMANO_BLOQUE),ceil((pmax.z-pmin.z+2)/TAMANO_BLOQUE),tamCubo);
    cout<<"tam("<<m->getTamX()<<","<<m->getTamY()<<","<<m->getTamZ()<<")"<<endl;
               for(auto c:md.caras){
                   vec3 v1=md.vert[c.x];
                   vec3 v2=md.vert[c.y];
                   vec3 v3=md.vert[c.z];
                   float da0=0.0f;
                   float tamda0=glm::max(glm::distance(v1,v3),glm::distance(v2,v3));
                   float fda0=1.0f/tamda0*0.5;
                   vec3 ori1=v1;
                   vec3 ori2=v2;
                   vec3 dir1=v3-v1;
                   vec3 dir2=v3-v2;
                   while(da0<=1.0f){
                       float da=0.0f;
                       vec3 ori=ori1+dir1*da0;
                       vec3 des=ori2+dir2*da0;
                       float tam=abs(glm::distance(ori,des));
                       vec3 dir=normalize(des-ori);
                       while(da<tam){
                           ivec3 voxp= ivec3(glm::floor(ori+dir*da));
                           Voxel& vox=m->getVoxel(voxp.x,voxp.y,voxp.z);
                           RGB color=RGB::conv(md.color[c.x]);
                           vector<RGB>::iterator it;
                           if((it=find(paleta.begin(),paleta.end(),color))==paleta.end()){
                              paleta.push_back(color);
                              vox.r=paleta.size()-1;
                           }else{
                              vox.r=std::distance(paleta.begin(),it);
                           }
                           da+=tamCubo*0.5;
                       }
                       da0+=fda0;
                   }

               }
    m->paleta.resize(0);
    for(RGB cpal:paleta){
        m->paleta.push_back(glm::vec3(((float)cpal.r)/255.0f,((float)cpal.g)/255.0f,((float)cpal.b)/255.0f));
    }


}
