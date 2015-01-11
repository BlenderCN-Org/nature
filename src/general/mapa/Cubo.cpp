#include "Cubo.h"
std::ostream& operator<<(std::ostream& o,Cubo c)
{
    o<<"cubo:p1("<<c.p1.x<<","<<c.p1.y<<","<<c.p1.z<<")t("<<c.t.x<<","<<c.t.y<<","<<c.t.z<<")c("<<c.c.x<<","<<c.c.y<<","<<c.c.z<<")";
    return o;
};
