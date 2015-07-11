#ifndef _REP_FACTORY_H_
#define _REP_FACTORY_H_
#include "entidades/Types.h"
#include "vista/RepSer.h"
#include "vista/RepMapCub.h"
#include <memory>
class RepFactory{
    public:
        static std::unique_ptr<RepSer> being(BeingType type);
        static std::unique_ptr<RepMapCub> mapa(Mapa& m);
};
#endif
