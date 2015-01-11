#ifndef _CUBO_H_
#define _CUBO_H_
#include "includeglm.h"
#include <iostream>

class Cubo{
    public:
        glm::vec3  p1;//punto
        glm::vec3  p2;//tamanio
        glm::vec3  t;//tamanio
        glm::vec3  c;//centro
        Cubo(glm::vec3 p1,glm::vec3 t){
            set(p1,t);
        }
        void set(glm::vec3 p1,glm::vec3 t){
            this->p1=p1;
            this->t=t;
            this->p2=p1+t;
            c=p1+(t*0.5f);
        }
};

std::ostream& operator<<(std::ostream& o,Cubo c);
#endif
