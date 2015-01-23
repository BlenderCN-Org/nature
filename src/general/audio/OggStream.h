#ifndef _OGG_STREAM_H_
#define _OGG_STREAM_H_
#include <iostream>
#include <vorbis/vorbisfile.h>
class OggStream{
    public:
        OggStream(std::string n);
        ~OggStream();
        int read(char *buffer,int length,bool bigendian,int word,bool issigned);
        int getChannels();
        int getRate();
    private:
        OggVorbis_File oggFile;
        bool valido;
        int bitstream;
        vorbis_info *pInfo;
};
#endif

