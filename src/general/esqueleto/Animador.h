#ifndef _ANIMADOR_H_
#define _ANIMADOR_H_
#include <vector>
#include <string>
#include <map>
#include "Esqueleto.h"
#include "includeglm.h"
class Animador{
    public:
        Animador(Esqueleto& e);
        void act(float dt);
        bool terminado();
        bool terminado(int id,float t);
        int actual();
        int id(std::string nombre);
        std::vector<glm::mat4> getPose(std::string animacion,float t){
            return getPose(hashs[animacion],t);
        };

        std::vector<glm::mat4> getPose(){
            return getPose(aniId,t);
        };
        std::vector<glm::mat4> getPose(int id,float t);
        void animar(std::string nombre,bool loop=false,bool reiniciar=false);
    private:
        std::map<std::string ,int > hashs;
        int aniId;
        float t;
        bool loop;
        Esqueleto& esq;
};
#endif

