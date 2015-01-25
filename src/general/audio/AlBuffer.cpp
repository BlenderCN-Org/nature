#include "AlBuffer.h"
AlBuffer::AlBuffer(){
//    alGenBuffers(1, &buffer);
}
AlBuffer::AlBuffer(const char* n){
    buffer=alutCreateBufferFromFile(n);
}
AlBuffer::~AlBuffer(){
    alDeleteBuffers(1, &buffer);
}
int AlBuffer::id(){
    return buffer;
}
