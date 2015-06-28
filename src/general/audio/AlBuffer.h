#ifndef _AL_BUFFER_H_
#define _AL_BUFFER_H_
#include <AL/al.h>
#include <AL/alc.h>
#include <string>
/*
 * Struct that holds the RIFF data of the Wave file.
 * The RIFF data is the meta data information that holds,
 * the ID, size and format of the wave file
 */
struct RIFF_Header {
  char chunkID[4];
  char da[4];//size not including chunkSize or chunkID
  char format[4];
};
//#include <AL/alut.h>
//
/*
 * Struct to hold fmt subchunk data for WAVE files.
 */
struct WAVE_Format {
  char subChunkID[4];
  int32_t subChunkSize;
  short audioFormat;
  short numChannels;
  int32_t sampleRate;
  int32_t byteRate;
  short blockAlign;
  short bitsPerSample;
};
/*
* Struct to hold the data of the wave file
*/
struct WAVE_Data {
  char subChunkID[4]; //should contain the word data
  int32_t subChunk2Size; //Stores the size of the data block
};
class AlBuffer{
    public:
        AlBuffer();
        AlBuffer(std::string n);
        
        ~AlBuffer();
        int id();
        bool loadWavFile(const std::string filename, ALuint* buffer, ALsizei* size, ALsizei* frequency, ALenum* format);
    private:
       ALuint buffer;
};
#endif
