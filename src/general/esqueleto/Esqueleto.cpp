#include "Esqueleto.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include "util/GestorRutas.h"
#include "config.h"
using namespace std;
void imprimirMatriz3(glm::mat4 mat){
    for(int y=0;y<4;y++){
        cout<<"(";
        for(int x=0;x<4;x++){
            cout<<(x>0?",":"")<<mat[x][y];
        }
        cout<<")"<<endl;
    }
 }
Esqueleto::Esqueleto(const string ruta){
       ifstream f;
       int nh; //numero de huesos
       int na; //numero de animaciones
       f.open(GestorRutas::getRuta(ruta),  ios::in |  ios::binary);
       if(!f.is_open()){
           cout<<"error abriendo"<<GestorRutas::getRuta(ruta)<< endl;
       }else{
            f.read((char*)&nh,sizeof(int));
            DEBUG(/*{{{*/
              cout<<sizeof(int)<<":huesos="<<nh<<endl;
              )/*}}}*/
            if(nh>0){
                huesos.resize(nh);
                f.read((char*)huesos.data(),sizeof(Hueso)*nh);
            }
            for(Hueso& h:huesos){
                glm::mat4 mat =glm::translate(glm::mat4(1.0f),h.cabeza)*glm::toMat4(glm::rotation(glm::vec3(0.0f),h.cola-h.cabeza));
                bindPoses.push_back(mat);
            //    imprimirMatriz3(mat);
                h.mat=mat;
            }
            f.read((char*)&na,sizeof(int));
            anims.resize(na);

            for(int i=0;i<na;i++){
               AnimEsqueleto& a=anims[i];
               int len;
               int cuadros;
               getline(f,a.nombre,'\0');
               
               f.read((char*)&cuadros,sizeof(int));
               a.cuadros.resize(cuadros);
               int k=0;
               for(CuadroEsqueleto& ce:a.cuadros){
                   k++;
                   f.read((char*)&ce.tiempo,sizeof(float));
                   ce.huesos.resize(huesos.size());
                   f.read((char*)ce.huesos.data(),sizeof(CuadroHueso)*huesos.size());
               }

            }
       }
      /* 
   cout<<"na:"<<na<<endl;
   for(AnimEsqueleto& a:anims){
       cout<<"nh:"<<huesos.size()<<endl;
       cout<<"**Animacion:"<<a.nombre<<endl;
       cout<<"cuadros: "<<a.cuadros.size()<<endl;
       
       for(CuadroEsqueleto& ce:a.cuadros){
           cout<<"\tt="<<ce.tiempo<<endl;
           //cout<<"nh:"<<ce.huesos.size()<<endl;
           int ih=0;
           for(CuadroHueso& ch:ce.huesos){
               cout<<std::fixed<<std::setprecision(4);
               cout<<"\t\tih="<<ih<<endl;
               cout<<"\t\t("<<ch.pos.x<<","<<ch.pos.y<<","<<ch.pos.z<<")";
               cout<<"("<<ch.rot.x<<","<<ch.rot.y<<","<<ch.rot.z<<","<<ch.rot.w<<")"<<endl;
               ih++;
           }
       }
   }*/
}

Esqueleto::~Esqueleto(){
}

std::vector<glm::mat4> Esqueleto::getPose(string animacion,float t){
    vector<glm::mat4> poses(huesos.size());
    int ic=0;
    int aniId=0;
    while(true){
        if(ic>=anims[aniId].cuadros.size()-1||anims[aniId].cuadros[ic+1].tiempo>t){
           break; 
        }else{
            ic++;
        }
    }
    //cout<<"Cuadro:"<<ic<<endl;
    vector<bool> calculado(huesos.size());
    for(int i=0;i<huesos.size();i++){
        CuadroHueso &h=anims[aniId].cuadros[ic].huesos[i];
        //if(i==2&&ic==0){
          //  cout<<"Probado Matriz Recyrsiva"<<endl;
            poses[i]=  h.getMat(huesos,anims[aniId].cuadros[ic].huesos,huesos[i],i); 
       // }
        //poses[i]=  h.getMat(); 
    }
    return move(poses);
}