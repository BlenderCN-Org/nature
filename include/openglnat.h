#ifndef OPENGLNAT_H_INCLUDED
#define OPENGLNAT_H_INCLUDED

#ifndef EMSCRIPTEN
#define GLEW_STATIC
#include <GL/glew.h>
#else
#define GL_GLEXT_PROTOTYPES 1   /* this includes the necessary X headers */
#endif

#include <GL/gl.h>
#include <GL/glext.h>

//#include <EGL/egl.h>
//#include <GLES2/gl2.h>


#endif // OPENGLNAT_H_INCLUDED
