#ifndef _TEXTURA_H_
#define _TEXTURA_H_
#include "openglnat.h"
#include "util/Imagen.h"
#include <string>
class Textura{
       public:
           Textura();
           Textura(const Imagen& i);
           Textura(std::string  path);
           Textura(const Textura&)=delete;
           Textura& operator=(const Textura&)=delete;
           Textura(Textura&&);
           Textura& operator=(Textura&&);
           ~Textura();
           void bind();
           GLuint id();
       private:
           GLuint texId=0;

};
#endif
