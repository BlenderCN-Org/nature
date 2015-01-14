#include "Mesh.h"

#include <fstream>
#include <iostream>
#include <memory>

using namespace std;

Mesh::Mesh(Mesh&& viejo){
   swap(vao,viejo.vao);
   vbo.swap(viejo.vbo);
   swap(nvert,viejo.nvert);
   swap(ncaras,ncaras); 
};
Mesh& Mesh::operator=(Mesh&& viejo){
   swap(vao,viejo.vao);
   vbo.swap(viejo.vbo);
   swap(nvert,viejo.nvert);
   swap(ncaras,ncaras); 
   return *this;
};

Mesh::Mesh(MeshDatos d)
{     
      usarVAO=false;
      nvert=d.vert.size();
      cout<<"vertices*:"<<nvert<<endl;
      ncaras=d.caras.size();
      glEnableVertexAttribArray(0);
      glGenBuffers(vbo.size(), &vbo[0]);
      glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); 
      glBufferData(GL_ARRAY_BUFFER, nvert*sizeof(float)*3, &d.vert[0], GL_STATIC_DRAW); 
      glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0); 


      //Colores
      glEnableVertexAttribArray(1);
      glBindBuffer(GL_ARRAY_BUFFER, vbo[1]); 
      glBufferData(GL_ARRAY_BUFFER, nvert*sizeof(float)*3, &d.color[0], GL_STATIC_DRAW); 

      glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0); 


      //Normales
      glEnableVertexAttribArray(2);
      glBindBuffer(GL_ARRAY_BUFFER, vbo[2]); 
      glBufferData(GL_ARRAY_BUFFER, nvert*sizeof(float)*3, &d.normal[0], GL_STATIC_DRAW); 
      glVertexAttribPointer((GLuint)2, 3, GL_FLOAT, GL_FALSE, 0, 0);

      //Id Huesos
      glEnableVertexAttribArray(3);
      glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
      glBufferData(GL_ARRAY_BUFFER, nvert*sizeof(float), &d.hueso[0], GL_STATIC_DRAW);
      glVertexAttribPointer((GLuint)3, 1, GL_FLOAT, GL_FALSE, 0, 0);
      //Peso
      glEnableVertexAttribArray(4);
      glBindBuffer(GL_ARRAY_BUFFER, vbo[4]);
      glBufferData(GL_ARRAY_BUFFER, nvert*sizeof(float), &d.peso[0], GL_STATIC_DRAW);
      glVertexAttribPointer((GLuint)4, 1, GL_FLOAT, GL_FALSE, 0, 0);
      //Uvs
      glEnableVertexAttribArray(5);
      glBindBuffer(GL_ARRAY_BUFFER, vbo[5]);
      glBufferData(GL_ARRAY_BUFFER, nvert*sizeof(float)*2, &d.uv[0], GL_STATIC_DRAW);
      glVertexAttribPointer((GLuint)5, 2, GL_FLOAT, GL_FALSE, 0, 0);
      //Oclussion
      glEnableVertexAttribArray(6);
      glBindBuffer(GL_ARRAY_BUFFER, vbo[6]);
      glBufferData(GL_ARRAY_BUFFER, nvert*sizeof(float)*4, &d.oclusion[0], GL_STATIC_DRAW);
      glVertexAttribPointer((GLuint)6, 4, GL_FLOAT, GL_FALSE, 0, 0);

    // Set up our vertex attributes pointer
    //Caras
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[7]); 
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, ncaras*sizeof(int)*3, &d.caras[0], GL_STATIC_DRAW);

      if(usarVAO){
        //glBindVertexArray(0);
      }
      GLenum error=glGetError();
      if(error==GL_NO_ERROR){
          cout<<"todo bien terminado"<< endl;
      }


}

Mesh::~Mesh()
{
   glDeleteBuffers(vbo.size(), &vbo[0]);
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

       //UV
       glEnableVertexAttribArray(5);
       glBindBuffer(GL_ARRAY_BUFFER, vbo[5]); // Bind our Vertex Buffer Object
       glVertexAttribPointer((GLuint)5, 2, GL_FLOAT, GL_FALSE, 0, 0);
       //aOclusion
       glEnableVertexAttribArray(6);
       glBindBuffer(GL_ARRAY_BUFFER, vbo[6]); // Bind our Vertex Buffer Object
       glVertexAttribPointer((GLuint)6, 4, GL_FLOAT, GL_FALSE, 0, 0);



      // Set up our vertex attributes pointer
     //Caras
       glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[7]); // Bind our Vertex Buffer Object

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
