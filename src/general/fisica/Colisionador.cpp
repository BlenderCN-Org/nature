#include "Colisionador.h"
#include <cmath>
using namespace std;
vector<Colision> Colisionador::revColision(Entidad& e,Mapa& m){
    vector<Colision> cols;
    Cubo ce= e.getCubo();
    for(int x=(int)ce.p1.x;x<((int)ce.p2.x)+1;x++){
        for(int y=(int)ce.p1.y;y<((int)ce.p2.y)+1;y++){
            for(int z=(int)ce.p1.z;z<((int)ce.p2.z)+1;z++){
                if(m.enRango(x,y,z)&&m.getVoxel(x,y,z).solido()){
                    Cubo cv= m.getCuboVoxel(x,y,z);
                    Colision c;

                        if(cv.p1.x < ce.p2.x&&ce.p1.x<cv.p2.x)
                        {
                          if(cv.p1.y < ce.p2.y&&ce.p1.y<cv.p2.y)
                          {
                             if(cv.p1.z < ce.p2.z&&ce.p1.z<cv.p2.z)
                              {
                                  c.colisiona=true;
                                  c.pos=glm::vec3(ce.p1.x,ce.p1.y,cv.p1.z+cv.t.z);
                                  glm::vec3 pdir= cv.c-ce.c;
                                  if(abs(pdir.x)>abs(pdir.y)&&abs(pdir.x)>abs(pdir.z)){
                                      c.adir=glm::vec3(1,1,0);
                                  }else if(abs(pdir.y)>abs(pdir.z)){
                                      c.adir=glm::vec3(1,1,0);
                                  }else{
                                      c.adir=glm::vec3(0,0,1);
                                  }
                                  cols.push_back(c);
                              }
                          }
                        }
                }
            }
        }
    }
        
    return move(cols);
}

