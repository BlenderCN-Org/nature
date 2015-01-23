#ifndef _PATH_H_
#define _PATH_H_
#include <string>

class Path
{
    public:
        Path();
        virtual ~Path();
        static std::string base();
        static std::string mesh(const  std::string& nombreMesh);
        static std::string res(const  std::string& recurso);
        static std::string shader(const  std::string& nombreMesh);
    protected:
    private:
};

#endif // GESTORRUTAS_H
