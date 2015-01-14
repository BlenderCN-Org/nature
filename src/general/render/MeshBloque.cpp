#include "MeshBloque.h"
#include <vector>
#include "includeglm.h"
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
using namespace glm;
void revisarError2(string modulo){
    GLenum error=glGetError();
    if(error==GL_NO_ERROR){
        //cout<<modulo<<": todo bien"<< endl;
     }else{
        //cout<<modulo<<": todo mal:"<<error<< endl;
    }
}
MeshBloque::MeshBloque(MeshBloque&& viejo){
   swap(vao,viejo.vao);
   vbo.swap(viejo.vbo);
   swap(nvert,viejo.nvert);
   swap(ncaras,ncaras); 
};
MeshBloque& MeshBloque::operator=(MeshBloque&& viejo){
   swap(vao,viejo.vao);
   vbo.swap(viejo.vbo);
   swap(nvert,viejo.nvert);
   swap(ncaras,ncaras); 
   return *this;
};
void MeshBloque::vertex(Mapa& m, Bloque& b){
     vector<vec3> ver;
     vector<vec4> ocl;
     vector<vec3> nor;
     vector<float> col;
     vector<unsigned int> caras;
     float f=m.getTamCubo();
     int i=0;
     for(int x=b.x;x<b.x+b.tam;++x){
         for(int y=b.y;y<b.y+b.tam;++y){
            for(int z=b.z;z<b.z+b.tam;++z){
                //cara1
                Voxel& vox=m.getVoxel(x,y,z);
                if(vox.solido()&&vox.borde){
                    vec3 pa=vec3(x,y,z);
                    vec3 v=vec3(1,0,0);
                    vec3 v2=vec3(1,0,1);//for ambient oclussion
                    vec3 v3=vec3(1,-1,0);//for ambient oclussion
                    vec3 v4=vec3(1,-1,1);//for ambient oclussion
                    vec3 centro=vec3(pa.x*f,pa.y*f,pa.z*f);

                    vec3 verca[4];
                    verca[0]={f/2,-f/2,+f/2};
                    verca[1]={f/2,+f/2,+f/2};
                    verca[2]={f/2,+f/2,-f/2};
                    verca[3]={f/2,-f/2,-f/2};

                    vec3 ocln[4];
                    ocln[0]=normalize(vec3(1,-1,1));
                    ocln[1]=normalize(vec3(1,1,1));
                    ocln[2]=normalize(vec3(1,1,-1));
                    ocln[3]=normalize(vec3(1,-1,-1));
                    mat3 r=toMat3(quat(radians(vec3(0,0,90))));

                    for(int i=0;i<6;i++){
                        if(i==3) r=toMat3(quat(radians(vec3(90,0,0))));
                        if(i==4) r=toMat3(quat(radians(vec3(180,0,0))));
                        vec3 p=pa+v;
                        if(m.enRango((int)round(p.x),(int)round(p.y),(int)round(p.z))
                           &&!(m.getVoxel((int)round(p.x),(int)round(p.y),(int)round(p.z)).solido())){
                            int size=ver.size();
                            vec3 voclu1=v2-v;
                            vec3 voclu2=v3-v;
                            vec3 voclu3=v4-v;
                            vec3 po1=p+voclu1;
                            vec3 po2=p+voclu2;
                            vec3 po3=p+voclu3;
                            for(int j=0;j<4;j++){
                                vec4 oc=vec4(ocln[j],0.0);
                                if(m.getVoxel((int)round(po1.x),(int)round(po1.y),(int)round(po1.z)).solido())
                                   oc.w+=0.3;
                                if (m.getVoxel((int)round(po3.x),(int)round(po3.y),(int)round(po3.z)).solido())
                                   oc.w+=0.3;
                                if(m.getVoxel((int)round(po2.x),(int)round(po2.y),(int)round(po2.z)).solido())
                                   oc.w+=0.3;
                                ver.push_back(centro+verca[j]);
                                nor.push_back(v);
                                vec3 caux=m.paleta[vox.r];
                                col.push_back(caux.r);col.push_back(caux.g);col.push_back(caux.b);
                                ocl.push_back(oc);
                                mat3 r2=toMat3(quat(radians(vec3(90,90,90)*-v)));
                                voclu1=r2*voclu1;
                                voclu2=r2*voclu2;
                                voclu3=r2*voclu3;
                                po1=p+voclu1;
                                po2=p+voclu2;
                                po3=p+voclu3;
                            }
                            if(ocl[ocl.size()-4].w+ocl[ocl.size()-1].w>ocl[ocl.size()-2].w+ocl[ocl.size()-3].w){
                                caras.push_back(size+3);
                                caras.push_back(size+1);
                                caras.push_back(size);

                                caras.push_back(size+3);
                                caras.push_back(size+2);
                                caras.push_back(size+1);
                            }else{
                                caras.push_back(size);
                                caras.push_back(size+2);
                                caras.push_back(size+1);

                                caras.push_back(size);
                                caras.push_back(size+3);
                                caras.push_back(size+2);
                            }
                        } 

                        v=r*v;
                        v2=r*v2;
                        v3=r*v3;
                        v4=r*v4;
                        for(int j=0;j<4;j++){
                            verca[j]=r*verca[j];
                            ocln[j]=r*ocln[j];
                        }
                    }
                }
            }
         }
     }
     ncaras=caras.size();
     nvert=ver.size()*3;
     //cout<<"i*3="<<i*3<<";vert"<<nvert<<endl;
    // revisarError2("iniciando generar mesh");
//     glGenVertexArrays(1, &vao);
  //   revisarError2("generar vao");
     //glBindVertexArray(vao);
//     revisarError2("bind vao");
     //cout<<"VAO creado="<<vao<<endl;
     //glEnableVertexAttribArray(0);

     glGenBuffers(vbo.size(), &vbo[0]);// Generate our Vertex Buffer Object
     revisarError2("generar buffers");
     glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); // Bind our Vertex Buffer Object

     glBufferData(GL_ARRAY_BUFFER, ver.size()*3*4, (float*)&ver[0], GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
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

     glBufferData(GL_ARRAY_BUFFER, nor.size()*3*4, (float*)&nor[0], GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
     revisarError2("llenar normales");
     glVertexAttribPointer((GLuint)2, 3, GL_FLOAT, GL_FALSE, 0, 0);

     // Set up our vertex attributes pointer
     //UV
     glEnableVertexAttribArray(5);
     glBindBuffer(GL_ARRAY_BUFFER, vbo[3]); // Bind our Vertex Buffer Object
     glBufferData(GL_ARRAY_BUFFER, ocl.size()*4, (float*)&ocl[0], GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
     revisarError2("llenar uv");
     glVertexAttribPointer((GLuint)5, 2, GL_FLOAT, GL_FALSE, 0, 0);

     // Set up our vertex attributes pointer
     //Oclussion
     glEnableVertexAttribArray(6);
     glBindBuffer(GL_ARRAY_BUFFER, vbo[4]); // Bind our Vertex Buffer Object
     glBufferData(GL_ARRAY_BUFFER, ocl.size()*4*4, (float*)&ocl[0], GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
     revisarError2("llenar oclusion");
     glVertexAttribPointer((GLuint)6, 4, GL_FLOAT, GL_FALSE, 0, 0);



     //Caras
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[5]); // Bind our Vertex Buffer Object
     glBufferData(GL_ELEMENT_ARRAY_BUFFER, caras.size()*sizeof(unsigned int), &caras[0], GL_STATIC_DRAW);



     //glBindVertexArray(0);
     GLenum error=glGetError();
     if(error==GL_NO_ERROR){
    //  cout<<"todo bien terminado"<< endl;
     }
     //cout<<"Vert="<<nvert<<";Caras="<<ncaras<<endl;

}
MeshBloque::MeshBloque(Mapa& m, Bloque& b)
{ 
    //cubo(m,b);
    vertex(m,b);
}
void MeshBloque::bindAtributtes(){
       glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); 
       glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0); 
       //Colores
       glEnableVertexAttribArray(1);
       glBindBuffer(GL_ARRAY_BUFFER, vbo[1]); 
       glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0); 
       //Normales
       glEnableVertexAttribArray(2);
       glBindBuffer(GL_ARRAY_BUFFER, vbo[2]); 
       glVertexAttribPointer((GLuint)2, 3, GL_FLOAT, GL_FALSE, 0, 0);
       //UV
       glEnableVertexAttribArray(5);
       glBindBuffer(GL_ARRAY_BUFFER, vbo[3]); 
       glVertexAttribPointer((GLuint)5, 2, GL_FLOAT, GL_FALSE, 0, 0);
       //Oclusion
       glEnableVertexAttribArray(6);
       glBindBuffer(GL_ARRAY_BUFFER, vbo[4]); 
       glVertexAttribPointer((GLuint)6, 4, GL_FLOAT, GL_FALSE, 0, 0);
     //Caras
       glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[5]); 
}
MeshBloque::~MeshBloque()
{
   glDeleteBuffers(vbo.size(), vbo.data());
   //glDeleteVertexArrays(1, &vao);
}
void MeshBloque::dibujar(Shader* shader,const glm::mat4 &modelMatrix,bool cullback){
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearDepthf(1.0);
    glEnable(GL_CULL_FACE);
    glCullFace(cullback?GL_BACK:GL_FRONT);
    shader->bind(modelMatrix);
    bindAtributtes();
    revisarError2("vertexArray Enable");
    glDrawElements(GL_TRIANGLES, ncaras,GL_UNSIGNED_INT, (void*)0 );
    shader->unbind();

}
