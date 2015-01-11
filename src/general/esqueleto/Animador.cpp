#include "Animador.h"
#include <iostream>
using namespace std;
using namespace glm;
Animador::Animador(Esqueleto& e):
    esq(e)
{
    for(int i=0;i<e.anims.size();i++){
        hashs[e.anims[i].nombre]=i;
    }
    aniId=0;
}

void Animador::animar(string n,bool loop,bool reiniciar){
    int idAux=hashs[n];
    if(reiniciar||idAux!=aniId){
  //      cout<<n<<":"<<aniId<<endl;
//        cout<<"reiniciando idAux,aniID: "<<idAux<<"("<<esq.anims[idAux].nombre<<"),"<<aniId<<"("<<esq.anims[aniId].nombre<<")"<<endl;
        aniId=idAux;
        t=0;
        this->loop=loop;
    }
}
int Animador::actual(){return aniId;};
int Animador::id(std::string nombre){return hashs[nombre];};
bool Animador::terminado(){
    return terminado(aniId,t);
}
bool Animador::terminado(int id,float t){
    return t>esq.anims[id].cuadros.back().tiempo;
}


void Animador::act(float dt){
    t+=dt;
    if(loop&&terminado())
       t=0;
}

vector<mat4> Animador::getPose(int id,float t){
    vector<mat4> poses(esq.huesos.size());
    int ic=0;
    while(true){
        if(ic>=esq.anims[id].cuadros.size()-1||esq.anims[id].cuadros[ic+1].tiempo>t){
           break; 
        }else{
            ic++;
        }
    }
    vector<bool> calculado(esq.huesos.size());
    for(int i=0;i<esq.huesos.size();i++){
        CuadroHueso &h=esq.anims[id].cuadros[ic].huesos[i];
        poses[i]=  h.getMat(esq.huesos,esq.anims[id].cuadros[ic].huesos,esq.huesos[i],i); 
    }
    return move(poses);
}
