#include "MeshEsqueleto.h"
#include <vector>
#include "includeglm.h"
#include <iostream>
using namespace std;
MeshEsqueleto::MeshEsqueleto(Esqueleto& e){
     vector<float> ver;
     vector<float> cabeza;
     vector<GLint> indices;
     vector<float> ihueso;
     int i=0;
     int ih=0;
     for(Hueso& h:e.huesos){
         ver.push_back(h.cabeza.x);
         ver.push_back(h.cabeza.y);
         ver.push_back(h.cabeza.z);
         cabeza.push_back(1);
         indices.push_back(i++);
         ihueso.push_back(ih);

         ver.push_back(h.cola.x);
         ver.push_back(h.cola.y);
         ver.push_back(h.cola.z);
         cabeza.push_back(0);
         indices.push_back(i++);
         ihueso.push_back(ih);
         ih++;
     }
     nhuesos=e.huesos.size();
     cout<<"ver.size()="<<ver.size()<<endl;
     cout<<"indices.size()="<<indices.size()<<endl;
     cout<<"cabeza.size()="<<cabeza.size()<<endl;
     cout<<"ihuesos.size()="<<ihueso.size()<<endl;
     for(int ind:ihueso){
         cout<<ind<<endl;
     }
     glEnableVertexAttribArray(0);
     glGenBuffers(4, &vbo[0]);// Generate our Vertex Buffer Object
     glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); // Bind our Vertex Buffer Object
     glBufferData(GL_ARRAY_BUFFER, ver.size()*sizeof(float), &ver[0], GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
     glVertexAttribPointer((GLint)0, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer

    /*es cabeza?*/ 
     glEnableVertexAttribArray(1);
     glBindBuffer(GL_ARRAY_BUFFER, vbo[1]); // Bind our Vertex Buffer Object
     glBufferData(GL_ARRAY_BUFFER, cabeza.size()*sizeof(float), &cabeza[0], GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
     glVertexAttribPointer((GLint)1, 1, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer

     /*color*/ 
     glEnableVertexAttribArray(2);
     glBindBuffer(GL_ARRAY_BUFFER, vbo[2]); // Bind our Vertex Buffer Object
     glBufferData(GL_ARRAY_BUFFER, ihueso.size()*sizeof(float), &ihueso[0], GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
     glVertexAttribPointer((GLint)2, 1, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer


     //LINEAS
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[3]); // Bind our Vertex Buffer Object
     glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(int), &indices[0], GL_STATIC_DRAW);
}
MeshEsqueleto::~MeshEsqueleto(){
   glDeleteBuffers(2, vbo);
}
void MeshEsqueleto::bindAtributos(){
       glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); // Bind our Vertex Buffer Object
       glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer
/**es cabeza*/


       glEnableVertexAttribArray(1);
       glBindBuffer(GL_ARRAY_BUFFER, vbo[1]); // Bind our Vertex Buffer Object
       glVertexAttribPointer((GLuint)1, 1, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer

       glEnableVertexAttribArray(2);
       glBindBuffer(GL_ARRAY_BUFFER, vbo[2]); // Bind our Vertex Buffer Object
       glVertexAttribPointer((GLuint)2, 1, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer

       glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[3]); // Bind our Vertex Buffer Object
} 
void MeshEsqueleto::dibujar(Shader* shader,const glm::mat4 &modelMatrix,vector<glm::mat4> pose,vector<glm::mat4> bindPoses){
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearDepthf(1.0);
    //glPointSize(4.0f);
    shader->bind(modelMatrix,pose,bindPoses);
    bindAtributos();
    glDrawElements(GL_LINES, nhuesos*2,GL_UNSIGNED_INT, (void*)0 );
    shader->unbind();
    //glPointSize(1.0f);

}
