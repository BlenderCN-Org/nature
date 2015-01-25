#include "OggBuffer.h"
#include <vector>
#include <AL/al.h>
#include <AL/alc.h>
using namespace std;
AlBuffer OggBuffer::cargar(string n ){
     AlBuffer b;
     const int buffersize=32768;
     OggStream s(n);
     vector<char> buffer;
     char bufferaux[buffersize];

     int bytes;
     do
     {
        // Read up to a buffer's worth of decoded sound data
        bytes = s.read(bufferaux, buffersize, false, 2, true);

        if (bytes < 0)
            {
            cout << "Error decodificando" << n << "..." << endl;
            }
        buffer.insert(buffer.end(), bufferaux, bufferaux + bytes);
     }while (bytes > 0);
     cout<<"Buffer size: "<<buffer.size()<<endl;
     cout<<"Rate:"<<s.getRate()<<endl;
     cout<<"Channels: "<<s.getChannels()<<endl;
    alBufferData(b.id(), s.getChannels()==1?AL_FORMAT_MONO16:AL_FORMAT_STEREO16,&buffer[0], static_cast<ALsizei>(buffer.size()), s.getRate());
    return move(b);
}
