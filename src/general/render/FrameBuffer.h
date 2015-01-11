#ifndef _FRAME_BUFFER_H_
#define _FRAME_BUFFER_H_
#include "Textura.h"
#include "openglnat.h"
class FrameBuffer{
    public:
        FrameBuffer();
        FrameBuffer(const FrameBuffer&)=delete;
        FrameBuffer& operator=(const FrameBuffer&)=delete;
        FrameBuffer(FrameBuffer&&);
        FrameBuffer& operator=(FrameBuffer&&);
        ~FrameBuffer();
        void bind();
        void unbind();
        GLuint id();
    private:
        unsigned int idFb=0;
};
#endif
