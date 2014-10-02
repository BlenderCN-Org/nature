#ifndef __LSYSTEM_H__
#define __LSYSTEM_H__


#include <string>
#include <vector>
#include <map>
#include "Rama.h"
#include "Arbol.h"


struct LTreeNodo{
    std::string letra;
    std::vector<LTreeNodo> hijos;
};

class LSystem{

public:
    void agrLetra(std::string nombre,Rama rama);
    void agrRegla(std::string letra,LTreeNodo nodo);
    void generar(Arbol &arbol,std::string letra);
    int maxNivel=2; 
private:
    std::map<std::string,Rama> letras;
    std::map<std::string,LTreeNodo> reglas;
    void generarLTree(LTreeNodo &nodo,int n);
    void generarRamas(Rama &rama,LTreeNodo raiz);
};

#endif
