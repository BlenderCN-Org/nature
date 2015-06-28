#ifndef _MANAGER_STRING_H_
#define _MANAGER_STRING_H_
#include <memory>
#include <map>
#include <string>
#include "Manager.h"
#include "entidades/Entidad.h"
class ManagerString:public Manager<ManagerString,std::string,Entidad>{
};
#endif
