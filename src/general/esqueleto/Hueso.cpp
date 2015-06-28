#include "Hueso.h"
#include "includeglm.h"
using namespace std;
using namespace glm;
vector<Esfera> Hueso::getEsferas(){
    vector<Esfera> es;
    for(int i=0;i<coli;i++){
      Esfera e;
      float l=glm::distance(cabeza,cola);
      e.r=l/((float)coli);
      vec3 v=(cola-cabeza);
      e.c=v/((float)coli)*((float)i)+v/((float)coli)/2.0f;
      es.push_back(e);
    } 
   return move(es);
}
