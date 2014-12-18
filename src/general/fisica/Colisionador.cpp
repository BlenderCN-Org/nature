#include "Colisionador.h"
#include <cmath>
using namespace std;
Colision Colisionador::revColision(Entidad e,Mapa m){
    Colision c;
    c.colisiona=false;
    int x=(int)roundf(e.pos.x);
    int y=(int)roundf(e.pos.y);
    int z=(int)roundf(e.pos.z);
    if(m.enRango(x,y,z)&&m.getVoxel(x,y,z).solido){
        Cubo cv= m.getCuboVoxel(x,y,z);
        Cubo ce= e.getCubo();
            if(abs(cv.p.x - ce.p.x) < cv.t.x + ce.t.x)
            {
              //check the Y axis
              if(abs(cv.p.y - ce.p.y) < cv.t.y + ce.t.y)
              {
                  //check the Z axis
                  if(abs(cv.p.z - ce.p.z) < cv.t.z + ce.t.z)
                  {
                      c.colisiona=true;
                      c.pos=glm::vec3(ce.p.x,ce.p.y,cv.p.z+cv.t.z);
                  }
              }
            }
    }
        
    return c;
}

