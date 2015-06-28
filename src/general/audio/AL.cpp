#include "AL.h"
using namespace std;
string OpenAl::error(){
    switch(alGetError()){
        case AL_INVALID_NAME:
            return "Invalid name";
        break;
        case AL_INVALID_ENUM:
            return " Invalid enum ";
        break;
        case AL_INVALID_VALUE:
            return " Invalid value ";
        break;
        case AL_INVALID_OPERATION:
            return " Invalid operation ";
        break;
        case AL_OUT_OF_MEMORY:
            return " Out of memory like! ";
        break;
    }    
 return "sin error";
}
