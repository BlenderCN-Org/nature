#ifndef GESTORRUTAS_H
#define GESTORRUTAS_H
#include <string>

class GestorRutas
{
    public:
        GestorRutas();
        virtual ~GestorRutas();
        static std::string getRutaDatos();
        static std::string getRutaMesh(const  std::string& nombreMesh);
        static std::string getRutaShader(const  std::string& nombreMesh);
    protected:
    private:
};

#endif // GESTORRUTAS_H
