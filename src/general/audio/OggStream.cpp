#include "OggStream.h"
#include <iostream>
#include <cstdio>

using namespace std;
OggStream::OggStream(std::string n){

    FILE *f;
    f = fopen(n.c_str(),"rb");
    if(f==NULL){
        cout<<"No se pudo abrir el archivo :"<<n<<endl;
        valido=false;
    }else{
        ov_open(f, &oggFile, NULL, 0);
        pInfo = ov_info(&oggFile, -1);
        valido=true;
    }
}
OggStream::~OggStream(){
   if(valido)
        ov_clear(&oggFile);
   
};
int OggStream::read(char *buffer,int length,bool bigendian,int word,bool issigned){
    return ov_read(&oggFile,buffer,length,bigendian?1:0,word,issigned?1:0,&bitstream);
};

int OggStream::getChannels(){
    return pInfo->channels;
}
int OggStream::getRate(){
    return pInfo->rate;
}
