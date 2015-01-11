#ifndef _SHADOW_MAP_H_
#define _SHADOW_MAP_H_
#include "FrameBuffer.h"
#include "Textura.h"
class ShadowMap{
    public:
        ShadowMap(int ancho,int alto);
        void bind(){fb.bind();

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        };
        void unbind(){fb.unbind();};
   
        Textura tdepth;
        Textura tcolor;
        FrameBuffer fb;

};
#endif
