#include "Iluminador.h"

void Iluminador::iluminar(Mapa *m,glm::vec3 vector){
/*   for(int x=0;x<TAMANO_MAPA*TAMANO_BLOQUE_HOR;++x){
       for(int y=0;y<TAMANO_MAPA*TAMANO_BLOQUE_HOR;++y){
           for(int z=0;z<TAMANO_BLOQUE_VER;++z){
	       Voxel v=m->getVoxel(x,y,z);
	       if(v.castShadow)
	         emitirSombra(m,x,y,z,v,vector);
	   }
       }
   }*/
}

void Iluminador::iluminar(Mapa* mapa,int x,int y,int z,Voxel &v,glm::vec3  vector){
              if(v.borde){

                       //std::cout<<"Iluminar("<<x<<","<<y<<","<<z<<")"<<std::endl;
                       mapa->getVoxel(x,y,z);
		    /*   Ogre::Ray rayo;
		       rayo.setOrigin(Ogre::Vector3{(float)x,(float)y,(float)z});
		       rayo.setDirection(vector);
		       bool continuar=true;
		       for(int xd=x;xd<x+40&&xd<TAMANO_MAPA*TAMANO_BLOQUE_HOR&&continuar;++xd){
			   for(int yd=y;yd<y+40&&yd<TAMANO_MAPA*TAMANO_BLOQUE_HOR&&continuar;++yd){
				for(int zd=z;zd<z+40&&zd<TAMANO_BLOQUE_VER&&continuar;++zd){
				      Voxel voxel=mapa->getVoxel(xd,yd,zd);

				     if(voxel.borde&&voxel.solido&&!(x==xd&&y==yd&&z==zd)&&rayo.intersects(Ogre::Sphere{Ogre::Vector3{(float)xd,(float)yd,(float)zd},0.5f}).first){
					v.ilum=0.0;
//               			std::cout<<"Sombreado("<<x<<","<<y<<","<<z<<")("<<xd<<","<<yd<<","<<zd<<")"<<std::endl;
 					continuar=false;
					v.ilum=0.8;
					//v.r=1.0;
					//v.b=1.0;
				     }

				}
			   }
		       }*/
	      }

}


void Iluminador::emitirSombra(Mapa* mapa,int x,int y,int z,Voxel &v,glm::vec3  vector){
/*    Ogre::Ray rayo;
    rayo.setOrigin(Ogre::Vector3{(float)x,(float)y,(float)z});
    rayo.setDirection(vector);
    for(float i=1.0;i<80;i+=1.0){
	Ogre::Vector3 vr=rayo.getPoint(i);

        if(mapa->enRango((int)vr.x,(int)vr.y,(int)vr.z)){
           Voxel voxelSombra=mapa->getVoxel((int)vr.x,(int)vr.y,(int)vr.z);
	   voxelSombra.ilum=0.4+0.9*(i/50);
	   voxelSombra.ilum=0.5;
           mapa->setVoxel((int)vr.x,(int)vr.y,(int)vr.z,voxelSombra);
        }

    }*/
}
