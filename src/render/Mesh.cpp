#include "Mesh.h"

#include <fstream>
#include <iostream>
#include <memory>
using namespace std;
Mesh::Mesh( string nombre)
{   usarVAO=true;

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

               //4=TAMANO_FLOAT
               f.read((char*)vert.get(),sizeof(float)*nvert*3);
               f.read((char*)normal.get(),sizeof(float)*nvert*3);
               f.read((char*)colores.get(),sizeof(float)*nvert*3);
               f.read((char*)&ncaras,sizeof(int));
               for(int i=0;i<nvert;i++){
                   vmin=glm::min(vmin,glm::vec3(normal.get()[3*i],normal.get()[3*i+1],normal.get()[3*i+2]));
                   //cout<<"n("<<normal.get()[3*i]<<","<<normal.get()[3*i+1]<<","<<normal.get()[3*i+2]<<")"<< endl;
               }
               cout<<"vmin("<<vmin.x<<","<<vmin.y<<","<<vmin.z<<")"<<endl;
               if(ncaras>0){
                       unique_ptr<int> caras{new int[ncaras*3]};
                      f.read((char*)caras.get(),sizeof(int)*ncaras*3);
                      if(usarVAO){
                           glGenVertexArrays(1, &vao); // Create our Vertex Array Object
                           glBindVertexArray(vao); // Bind our Vertex Array Object so we can use it
                       }


                      glEnableVertexAttribArray(0);
                      glGenBuffers(4, &vbo[0]);// Generate our Vertex Buffer Object
                      glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); // Bind our Vertex Buffer Object

                      glBufferData(GL_ARRAY_BUFFER, nvert*4*3, vert.get(), GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW

                      glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer




                      //Colores
                      glEnableVertexAttribArray(1);
                      glBindBuffer(GL_ARRAY_BUFFER, vbo[1]); // Bind our Vertex Buffer Object
                      glBufferData(GL_ARRAY_BUFFER, nvert*4*3, colores.get(), GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW

                      glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer


                      //Normales
                      glEnableVertexAttribArray(2);
                      glBindBuffer(GL_ARRAY_BUFFER, vbo[2]); // Bind our Vertex Buffer Object
                      glBufferData(GL_ARRAY_BUFFER, nvert*4*3, normal.get(), GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW

                      glVertexAttribPointer((GLuint)2, 3, GL_FLOAT, GL_FALSE, 0, 0);

                     // Set up our vertex attributes pointer


          //Caras
                      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[3]); // Bind our Vertex Buffer Object
                      glBufferData(GL_ELEMENT_ARRAY_BUFFER, ncaras*sizeof(int)*3, caras.get(), GL_STATIC_DRAW);


                      if(usarVAO){// Disable our Vertex Array Object
                        glBindVertexArray(0);
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
   glDeleteBuffers(4, vbo);
   glDeleteVertexArrays(1, &vao);
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
       //glBufferData(GL_ARRAY_BUFFER, nvert*4*3, normal.get(), GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW

       glVertexAttribPointer((GLuint)2, 3, GL_FLOAT, GL_FALSE, 0, 0);

      // Set up our vertex attributes pointer


     //Caras
       glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[3]); // Bind our Vertex Buffer Object

}
void revisarError(string modulo){
    GLenum error=glGetError();
    if(error==GL_NO_ERROR){
      //  cout<<modulo<<": todo bien"<< endl;
     }else{
     //   cout<<modulo<<": todo mal:"<<error<< endl;
    }
}
void Mesh::dibujar(Shader* shader,const glm::mat4 &modelMatrix)
{ // Bind our Vertex Array Object
     //glColor3f(0.0, 0.0,1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearDepth(1.0);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
     shader->bind(modelMatrix);
     revisarError("shader");
     //glShadeModel(GL_FLAT);
     if(!usarVAO){

         // bindAtributtes();
     }else{
          glBindVertexArray(vao);
     }
     revisarError("atributos");

     revisarError("vertexArray Enable");
     glDrawElements(GL_TRIANGLES, ncaras*3,GL_UNSIGNED_INT, (void*)0 ); // Draw our square
     revisarError("draw elements");
     revisarError("vertexArray Disable");
     shader->unbind();
     revisarError("shader unbind");
    //  cout<<"dibujado"<< endl;
     if(usarVAO){
          glEnableVertexAttribArray(0);
          glBindVertexArray(0);
     }


     //glColor3f(0.0,0.0,0.0);


}
