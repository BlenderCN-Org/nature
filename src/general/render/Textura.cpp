#include "Textura.h"
#include <utility>

using namespace std;
Textura::Textura(){
    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);

}
Textura::Textura(const Imagen& i){
    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, i.ancho,i.alto, 0, i.ncom==3?GL_RGB:GL_RGBA, GL_UNSIGNED_BYTE, i.image_data.get());
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
};
Textura::Textura(Textura&& n){
    swap(texId,n.texId);

};
Textura& Textura::operator=(Textura&& n){
    swap(texId,n.texId);
    return *this;
};


Textura::~Textura(){
    glDeleteTextures(1,&texId);
};
void Textura::Textura::bind(){
    glBindTexture(GL_TEXTURE_2D, texId);
};

GLuint Textura::id(){
    return texId;
}
