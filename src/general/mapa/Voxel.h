
#ifndef __Voxel_h_
#define __Voxel_h_
struct Voxel{
      public:
      bool  borde:1;
//      bool solido=false;
      unsigned char r:7;//color r
      bool solido(){ return r!=0;}
//      unsigned char g;//color g
//      unsigned char b;//color b
//      unsigned char a;//color a

};
#endif
