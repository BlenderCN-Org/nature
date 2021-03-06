#include "Esqueleto.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include "util/Path.h"
#include "config.h"
#include <assert.h>
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
       f.open(Path::res(ruta),  ios::in |  ios::binary);
       if(!f.is_open()){
           cout<<"error abriendo"<<Path::res(ruta)<< endl;
       }else{
            f.read((char*)&nh,sizeof(int));
            DEBUG(/*{{{*/
              cout<<sizeof(int)<<":huesos="<<nh<<endl;
              )/*}}}*/
            if(nh>0){
//                huesos.resize(nh);
                for(int i=0;i<nh;i++){
                    Hueso h;
                    cout<<"leer huesos"<<endl;
                    getline(f,h.nombre,'\0');
                    f.read((char*)&h.padre,sizeof(h.padre));
                    f.read((char*)&h.cabeza,sizeof(h.cabeza));
                    f.read((char*)&h.cola,sizeof(h.cola));
                    f.read((char*)&h.mat,sizeof(h.mat));
                    f.read((char*)&h.coli,sizeof(h.coli));
                    huesos.push_back(h);
                }
            }

            cout<<"huesos leidos"<<endl;
            for(Hueso& h:huesos){
                glm::mat4 mat =glm::translate(glm::mat4(1.0f),h.cabeza)*glm::toMat4(glm::rotation(glm::vec3(0.0f),h.cola-h.cabeza));
                bindPoses.push_back(mat);
            //    imprimirMatriz3(mat);
                h.mat=mat;
            }

            cout<<"leer animaciones"<<endl;


            f.read((char*)&na,sizeof(int));

            assert(na<100);
            cout<<"anims:"<<na<<endl;
            anims.resize(na);

            for(int i=0;i<na;i++){
               AnimEsqueleto& a=anims[i];
               int len;
               int cuadros;
               getline(f,a.nombre,'\0');
               cout<<"leer cuadros"<<endl;
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

int Esqueleto::getHueso(){
    for(int i=0;i<huesos.size();i++){
        Hueso &h=huesos[i];
        if(h.nombre.compare("arma")==0){
   //         cout<<"encontrado"<<endl;
            return i;  
        }
    }
    return -1;
}
Esqueleto::~Esqueleto(){
}


