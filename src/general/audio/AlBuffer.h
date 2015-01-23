#ifndef _AL_BUFFER_H_
#define _AL_BUFFER_H_
#include <AL/al.h>
#include <AL/alc.h>
class AlBuffer{
    public:
        AlBuffer();
        ~AlBuffer();
        int id();
    private:
       ALuint buffer;
};
#endif
