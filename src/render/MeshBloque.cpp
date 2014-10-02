#include "MeshBloque.h"
#include <vector>
#include "includeglm.h"
#include "Mesh.h"
using namespace std;
void revisarError2(string modulo){
    GLenum error=glGetError();
    if(error==GL_NO_ERROR){
        //cout<<modulo<<": todo bien"<< endl;
     }else{
        //cout<<modulo<<": todo mal:"<<error<< endl;
    }
}
MeshBloque::MeshBloque(Mapa& m, Bloque& b)
{
     vector<float> ver;
     vector<float> nor;
     vector<float> col;
     vector<unsigned int> caras;
     float f=1;
     int i=0;
     for(int x=b.x;x<b.x+b.tam;++x){
         for(int y=b.y;y<b.y+b.tam;++y){
            for(int z=b.z;z<b.z+b.tam;++z){
                Voxel& v=m.getVoxel(x,y,z);
                if(v.solido&&v.borde){
                  glm::vec3 p[8];
                  glm::vec3 n[8];
                  p[0]={x*f-f/2,y*f-f/2,z*f-f/2};n[0]={-0.33,-0.33,-0.33};
                  p[1]={x*f-f/2,y*f+f/2,z*f-f/2};n[1]={-0.33,+0.33,-0.33};
                  p[2]={x*f+f/2,y*f+f/2,z*f-f/2};n[2]={+0.33,+0.33,-0.33};
                  p[3]={x*f+f/2,y*f-f/2,z*f-f/2};n[3]={+0.33,-0.33,-0.33};
                  p[4]={x*f-f/2,y*f-f/2,z*f+f/2};n[4]={-0.33,-0.33,+0.33};
                  p[5]={x*f-f/2,y*f+f/2,z*f+f/2};n[5]={-0.33,+0.33,+0.33};
                  p[6]={x*f+f/2,y*f+f/2,z*f+f/2};n[6]={+0.33,+0.33,+0.33};
                  p[7]={x*f+f/2,y*f-f/2,z*f+f/2};n[7]={+0.33,-0.33,+0.33};
                  for(int k=0;k<8;++k){
                      ver.push_back(p[k].x);ver.push_back(p[k].y);ver.push_back(p[k].z);
                      nor.push_back(n[k].x);nor.push_back(n[k].y);nor.push_back(n[k].z);
                      col.push_back(((float)v.r)/255.0f);col.push_back(((float)v.g)/255.0f);col.push_back(((float)v.b)/255.0f);
                  }
                  caras.push_back(i);caras.push_back(i+5);caras.push_back(i+1);
                  caras.push_back(i);caras.push_back(i+4);caras.push_back(i+5);

                  caras.push_back(i+1);caras.push_back(i+6);caras.push_back(i+2);
                  caras.push_back(i+1);caras.push_back(i+5);caras.push_back(i+6);

                  caras.push_back(i+2);caras.push_back(i+7);caras.push_back(i+3);
                  caras.push_back(i+2);caras.push_back(i+6);caras.push_back(i+7);

                  caras.push_back(i+3);caras.push_back(i+4);caras.push_back(i);
                  caras.push_back(i+3);caras.push_back(i+7);caras.push_back(i+4);

                  caras.push_back(i+3);caras.push_back(i+1);caras.push_back(i+2);
                  caras.push_back(i+3);caras.push_back(i);caras.push_back(i+1);

                  caras.push_back(i+4);caras.push_back(i+6);caras.push_back(i+5);
                  caras.push_back(i+4);caras.push_back(i+7);caras.push_back(i+6);
                  i+=8;
               }
            }
         }
     }
     ncaras=caras.size();
     nvert=ver.size();
     //cout<<"i*3="<<i*3<<";vert"<<nvert<<endl;
     revisarError2("iniciando generar mesh");
     glGenVertexArrays(1, &vao);
     revisarError2("generar vao");
     glBindVertexArray(vao);
     revisarError2("bind vao");
     //cout<<"VAO creado="<<vao<<endl;
     glEnableVertexAttribArray(0);
     glGenBuffers(4, &vbo[0]);// Generate our Vertex Buffer Object
     revisarError2("generar buffers");
     glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); // Bind our Vertex Buffer Object

     glBufferData(GL_ARRAY_BUFFER, ver.size()*4, &ver[0], GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
     revisarError2("llenar vertices");
     glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer




     //Colores
     glEnableVertexAttribArray(1);
     glBindBuffer(GL_ARRAY_BUFFER, vbo[1]); // Bind our Vertex Buffer Object
     glBufferData(GL_ARRAY_BUFFER, col.size()*4, &col[0], GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
     revisarError2("llenar colores");
     glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer


     //Normales
     glEnableVertexAttribArray(2);
     glBindBuffer(GL_ARRAY_BUFFER, vbo[2]); // Bind our Vertex Buffer Object

     glBufferData(GL_ARRAY_BUFFER, nor.size()*4, &nor[0], GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
     revisarError2("llenar normales");
     glVertexAttribPointer((GLuint)2, 3, GL_FLOAT, GL_FALSE, 0, 0);

     // Set up our vertex attributes pointer


     //Caras
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[3]); // Bind our Vertex Buffer Object
     glBufferData(GL_ELEMENT_ARRAY_BUFFER, caras.size()*sizeof(unsigned int), &caras[0], GL_STATIC_DRAW);



     glBindVertexArray(0);
     GLenum error=glGetError();
     if(error==GL_NO_ERROR){
    //  cout<<"todo bien terminado"<< endl;
     }
     //cout<<"Vert="<<nvert<<";Caras="<<ncaras<<endl;

}

MeshBloque::~MeshBloque()
{
   //cout<<"*******Destruyendo:"<<vao<<endl;
   glDeleteBuffers(4, vbo);
   glDeleteVertexArrays(1, &vao);
}
void MeshBloque::dibujar(Shader* shader,const glm::mat4 &modelMatrix){
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearDepth(1.0);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
     shader->bind(modelMatrix);
     //revisarError2("shader");
     //glShadeModel(GL_FLAT);

     glBindVertexArray(vao);
    // cout<<"VAo="<<vao<<endl;;
     //revisarError2("atributos mehs");

     revisarError2("vertexArray Enable");
     glDrawElements(GL_TRIANGLES, ncaras,GL_UNSIGNED_INT, (void*)0 );
    // revisarError2("draw elements");

     shader->unbind();
  //   revisarError2("shader unbind");
    // cout<<"dibujado"<< endl;

     glEnableVertexAttribArray(0);
     glBindVertexArray(0);


}
