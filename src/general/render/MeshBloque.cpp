#include "MeshBloque.h"
#include <vector>
#include "includeglm.h"
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
using namespace glm;

MeshDatos MeshBloque::generar(Mapa& m, Bloque& b){
     MeshDatos md;
     float f=m.getTamCubo();
     int i=0;
     for(int x=b.x;x<b.x+b.tam;++x){
         for(int y=b.y;y<b.y+b.tam;++y){
            for(int z=b.z;z<b.z+b.tam;++z){
                //cara1
                Voxel& vox=m.getVoxel(x,y,z);
                if(vox.solido()&&vox.borde){
                    vec3 pa=vec3(x,y,z);
                    vec3 v=vec3(1,0,0);
                    vec3 v2=vec3(1,0,1);//for ambient oclussion
                    vec3 v3=vec3(1,-1,0);//for ambient oclussion
                    vec3 v4=vec3(1,-1,1);//for ambient oclussion
                    vec3 centro=vec3(pa.x*f,pa.y*f,pa.z*f);

                    vec3 verca[4];
                    verca[0]={f/2,-f/2,+f/2};
                    verca[1]={f/2,+f/2,+f/2};
                    verca[2]={f/2,+f/2,-f/2};
                    verca[3]={f/2,-f/2,-f/2};

                    vec3 ocln[4];
                    ocln[0]=normalize(vec3(1,-1,1));
                    ocln[1]=normalize(vec3(1,1,1));
                    ocln[2]=normalize(vec3(1,1,-1));
                    ocln[3]=normalize(vec3(1,-1,-1));
                    mat3 r=toMat3(quat(radians(vec3(0,0,90))));

                    for(int i=0;i<6;i++){
                        if(i==3) r=toMat3(quat(radians(vec3(90,0,0))));
                        if(i==4) r=toMat3(quat(radians(vec3(180,0,0))));
                        vec3 p=pa+v;
                        if(m.enRango((int)round(p.x),(int)round(p.y),(int)round(p.z))
                           &&!(m.getVoxel((int)round(p.x),(int)round(p.y),(int)round(p.z)).solido())){
                            int size=md.vert.size();
                            vec3 voclu1=v2-v;
                            vec3 voclu2=v3-v;
                            vec3 voclu3=v4-v;
                            vec3 po1=p+voclu1;
                            vec3 po2=p+voclu2;
                            vec3 po3=p+voclu3;
                            for(int j=0;j<4;j++){
                                vec4 oc=vec4(ocln[j],0.0);
                                if(m.getVoxel((int)round(po1.x),(int)round(po1.y),(int)round(po1.z)).solido())
                                   oc.w+=0.3;
                                if (m.getVoxel((int)round(po3.x),(int)round(po3.y),(int)round(po3.z)).solido())
                                   oc.w+=0.3;
                                if(m.getVoxel((int)round(po2.x),(int)round(po2.y),(int)round(po2.z)).solido())
                                   oc.w+=0.3;
                                md.vert.push_back(centro+verca[j]);
                                md.normal.push_back(v);
                                vec3 caux=m.paleta[vox.r];
                                md.color.push_back(caux);
                                md.oclusion.push_back(oc);
                                mat3 r2=toMat3(quat(radians(vec3(90,90,90)*-v)));
                                voclu1=r2*voclu1;
                                voclu2=r2*voclu2;
                                voclu3=r2*voclu3;
                                po1=p+voclu1;
                                po2=p+voclu2;
                                po3=p+voclu3;
                            }
                            auto& ocl=md.oclusion;
                            if(ocl[ocl.size()-4].w+ocl[ocl.size()-1].w>ocl[ocl.size()-2].w+ocl[ocl.size()-3].w){
                                md.caras.push_back(ivec3(size+3,size+1,size));
                                md.caras.push_back(ivec3(size+3,size+2,size+1));
                            }else{
                                md.caras.push_back(ivec3(size,size+2,size+1));
                                md.caras.push_back(ivec3(size,size+3,size+2));
                            }
                        } 

                        v=r*v;
                        v2=r*v2;
                        v3=r*v3;
                        v4=r*v4;
                        for(int j=0;j<4;j++){
                            verca[j]=r*verca[j];
                            ocln[j]=r*ocln[j];
                        }
                    }
                }
            }
         }
     }
     md.hueso.resize(md.vert.size());
     md.peso.resize(md.vert.size());
     md.uv.resize(md.vert.size());
     return move(md);
}
