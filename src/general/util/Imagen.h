#ifndef _IMAGE_H_
#define _IMAGE_H_
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "includeglm.h"
#include "png.h"
struct RGB{
    png_byte r,g,b;
};
bool operator==(RGB c1,RGB c2);
std::ostream& operator<<(std::ostream& o,RGB c);
bool operator!=(RGB c1,RGB c2);
class Imagen{
    public:
      Imagen(std::string ruta);
      std::unique_ptr<png_byte> image_data;
      int alto;
      int ancho;
      int ncom=3;// numero de componentes
      RGB getPixel(int x,int y){
          RGB color{0,0,0};
         if(x<ancho&&y<alto)
             memcpy(&color,image_data.get()+(y*ancho*ncom+x*ncom),sizeof(RGB));
          return color;
      }

      
};
#endif
