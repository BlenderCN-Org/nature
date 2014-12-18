#include "Mesh.h"

#include <fstream>
#include <iostream>
#include <memory>
using namespace std;
Mesh::Mesh(string nombre)
{   usarVAO=false;

        ifstream f;
       f.open(GestorRutas::getRutaMesh(nombre),  ios::in |  ios::binary);
       if(!f.is_open()){
           cout<<"error abriendo"<<GestorRutas::getRutaMesh(nombre)<< endl;
       }else{
            glm::vec3 vmin=glm::vec3(1000.0f,1000.0f,1000.0f);
            f.read((char*)&nvert,sizeof(int));
              cout<<sizeof(int)<<":vertices="<<nvert<< endl;
            if(nvert>0){
               //vert= unique_ptr<float>(new float[nvert*3]);
               unique_ptr<float[]> vert{new float[nvert*3]};
               unique_ptr<float[]> normal{new float[nvert*3]};
               unique_ptr<float[]> colores{new float[nvert*3]};
               unique_ptr<float[]> idhueso{new float[nvert]};
               unique_ptr<float[]> peso{new float[nvert]};//peso del hueso

               //4=TAMANO_FLOAT
               f.read((char*)vert.get(),sizeof(float)*nvert*3);
               f.read((char*)normal.get(),sizeof(float)*nvert*3);
               f.read((char*)colores.get(),sizeof(float)*nvert*3);
               f.read((char*)idhueso.get(),sizeof(float)*nvert);
               f.read((char*)peso.get(),sizeof(float)*nvert);

               f.read((char*)&ncaras,sizeof(int));
               for(int i=0;i<nvert;i++){
                   vmin=glm::min(vmin,glm::vec3(normal.get()[3*i],normal.get()[3*i+1],normal.get()[3*i+2]));
               }
               if(ncaras>0){
                       unique_ptr<GLuint> caras{new GLuint[ncaras*3]};
                      f.read((char*)caras.get(),sizeof(GLuint)*ncaras*3);
                      if(usarVAO){
                       }
                      //cout<<sizeof(int)<<":caras="<<nvert<< endl;


                      glEnableVertexAttribArray(0);
                      glGenBuffers(6, &vbo[0]);
                      glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); 
                      glBufferData(GL_ARRAY_BUFFER, nvert*sizeof(float)*3, vert.get(), GL_STATIC_DRAW); 

                      glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0); 




                      //Colores
                      glEnableVertexAttribArray(1);
                      glBindBuffer(GL_ARRAY_BUFFER, vbo[1]); 
                      glBufferData(GL_ARRAY_BUFFER, nvert*sizeof(float)*3, colores.get(), GL_STATIC_DRAW); 

                      glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0); 


                      //Normales
                      glEnableVertexAttribArray(2);
                      glBindBuffer(GL_ARRAY_BUFFER, vbo[2]); 
                      glBufferData(GL_ARRAY_BUFFER, nvert*sizeof(float)*3, normal.get(), GL_STATIC_DRAW); 
                      glVertexAttribPointer((GLuint)2, 3, GL_FLOAT, GL_FALSE, 0, 0);

                      //Id Huesos
                      glEnableVertexAttribArray(3);
                      glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
                      glBufferData(GL_ARRAY_BUFFER, nvert*sizeof(float), idhueso.get(), GL_STATIC_DRAW);
                      glVertexAttribPointer((GLuint)3, 1, GL_FLOAT, GL_FALSE, 0, 0);
                      //Peso
                      glEnableVertexAttribArray(4);
                      glBindBuffer(GL_ARRAY_BUFFER, vbo[4]);
                      glBufferData(GL_ARRAY_BUFFER, nvert*sizeof(float), peso.get(), GL_STATIC_DRAW);
                      glVertexAttribPointer((GLuint)4, 1, GL_FLOAT, GL_FALSE, 0, 0);

                     // Set up our vertex attributes pointer


          //Caras
                      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[5]); 
                      glBufferData(GL_ELEMENT_ARRAY_BUFFER, ncaras*sizeof(int)*3, caras.get(), GL_STATIC_DRAW);


                      if(usarVAO){
                        //glBindVertexArray(0);
                      }
                      GLenum error=glGetError();
                      if(error==GL_NO_ERROR){
                          cout<<"todo bien terminado"<< endl;
                      }
               }


            }
       }
}

Mesh::~Mesh()
{
   glDeleteBuffers(6, vbo);
   //glDeleteVertexArrays(1, &vao);
}
void Mesh::bindAtributtes(){
       glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); // Bind our Vertex Buffer Object
       glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer




       //Colores
       glEnableVertexAttribArray(1);
       glBindBuffer(GL_ARRAY_BUFFER, vbo[1]); // Bind our Vertex Buffer Object
       glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer


       //Normales
       glEnableVertexAttribArray(2);
       glBindBuffer(GL_ARRAY_BUFFER, vbo[2]); // Bind our Vertex Buffer Object
       glVertexAttribPointer((GLuint)2, 3, GL_FLOAT, GL_FALSE, 0, 0);
       //IdHueso
       glEnableVertexAttribArray(3);
       glBindBuffer(GL_ARRAY_BUFFER, vbo[3]); // Bind our Vertex Buffer Object
       glVertexAttribPointer((GLuint)3, 1, GL_FLOAT, GL_FALSE, 0, 0);
       //Peso
       glEnableVertexAttribArray(4);
       glBindBuffer(GL_ARRAY_BUFFER, vbo[4]); // Bind our Vertex Buffer Object
       glVertexAttribPointer((GLuint)4, 1, GL_FLOAT, GL_FALSE, 0, 0);


      // Set up our vertex attributes pointer
     //Caras
       glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[5]); // Bind our Vertex Buffer Object

}
void revisarError(string modulo){
    GLenum error=glGetError();
    if(error==GL_NO_ERROR){
      //  cout<<modulo<<": todo bien"<< endl;
     }else{
     //   cout<<modulo<<": todo mal:"<<error<< endl;
    }
}
void Mesh::dibujar(Shader* shader,const glm::mat4 &modelMatrix,bool cullBack)
{ 
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(cullBack?GL_BACK:GL_FRONT);
    shader->bind(modelMatrix);
     if(!usarVAO){
          bindAtributtes();
     }else{
     }
     glDrawElements(GL_TRIANGLES, ncaras*3,GL_UNSIGNED_INT, (void*)0 ); // Draw our square
     shader->unbind();
     if(usarVAO){
     }
}

void Mesh::dibujar(Shader* shader,const glm::mat4 &modelMatrix,vector<glm::mat4> pose,vector<glm::mat4> bindPoses,bool cullBack){
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(cullBack?GL_BACK:GL_FRONT);
    shader->bind(modelMatrix,pose,bindPoses);
     if(!usarVAO){
          bindAtributtes();
     }else{
     }
     glDrawElements(GL_TRIANGLES, ncaras*3,GL_UNSIGNED_INT, (void*)0 ); // Draw our square
     shader->unbind();
     if(usarVAO){
     }
   shader->unbind();
}
