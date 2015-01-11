#include "FrameBuffer.h"
#include <utility>
using namespace std;
FrameBuffer::FrameBuffer(){
   GLuint FramebufferName = 0;
   glGenFramebuffers(1, &idFb);
}
FrameBuffer::FrameBuffer(FrameBuffer&& n){
    swap(this->idFb,n.idFb);
};
FrameBuffer& FrameBuffer::operator=(FrameBuffer&& n){
    swap(this->idFb,n.idFb);
    return *this;
}
FrameBuffer::~FrameBuffer(){
    glDeleteFramebuffers(1,&idFb);
};
void FrameBuffer::bind(){
    glBindFramebuffer(GL_FRAMEBUFFER,idFb);
};
void FrameBuffer::unbind(){
    glBindFramebuffer(GL_FRAMEBUFFER,0);
}
GLuint FrameBuffer::id(){
    return idFb;
};

