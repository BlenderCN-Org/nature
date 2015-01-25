#ifndef _AL_BUFFER_H_
#define _AL_BUFFER_H_
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

class AlBuffer{
    public:
        AlBuffer();
        AlBuffer(const char* n);
        ~AlBuffer();
        int id();
    private:
       ALuint buffer;
};
#endif
