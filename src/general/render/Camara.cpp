#include "Camara.h"

Camara::Camara(float av,float proporcion,float cercano,float lejano)
{
     this->mProy=glm::perspective(glm::radians(av), proporcion, cercano, lejano);
}

Camara::~Camara()
{
     //dtor
}
