#include "LSystem.h"


void LSystem::agrLetra(std::string nombre,Rama rama){
   letras[nombre]=rama;
}
void LSystem::agrRegla(std::string letra,LTreeNodo letras){
   reglas[letra]=letras;

}

void LSystem::generarRamas(Rama &rama,LTreeNodo raiz){
   rama=letras[raiz.letra];

   //std::cout<<"Rama hijos Raiz:"<<raiz.hijos.size()<<std::endl;
   for(auto hijo:raiz.hijos){
      Rama rhijo;
      generarRamas(rhijo,hijo);


      //std::cout<<"Rama rhijo:"<<rhijo.hijos.size()<<std::endl;
      rama.hijos.push_back(std::move(rhijo));

      //std::cout<<"Rama hijos:"<<rama.hijos[rama.hijos.size()-1].hijos.size()<<std::endl;

   }

}
void LSystem::generarLTree(LTreeNodo &nodo,int n){
   if(!(reglas.find(nodo.letra)==reglas.end())){
      nodo =reglas[nodo.letra];
   }
   //std::cout<<"nivel:"<<n<<std::endl;
   if(n<maxNivel){

      for(unsigned int i=0;i<nodo.hijos.size();++i){
         LTreeNodo &hijo=nodo.hijos[i];
         generarLTree(hijo,n+1);

      }
   }

}
void LSystem::generar(Arbol &arbol,std::string letra){
   LTreeNodo raiz;
   raiz.letra=letra;
   generarLTree(raiz,0);
   generarRamas(arbol.raiz,raiz);


}
