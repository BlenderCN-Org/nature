#include "ShaTexture.h"
void ShaTexture::setTexColor(Shader& sha,Textura& tex){
   glActiveTexture(GL_TEXTURE0);
   tex.bind();
   sha.setint("texColor",0);
}

