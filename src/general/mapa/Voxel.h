
#ifndef __Voxel_h_
#define __Voxel_h_
enum class VoxelType{
        Planta,
        Tierra,
        Piedra
};
struct Voxel{
      public:
      bool  borde:1;
//      bool solido=false;
      unsigned char r:7;//color r
      bool solido(){ return r!=0;}

};
#endif
