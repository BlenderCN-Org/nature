#version 330
// atributos
layout(location = 0) in  vec3 in_Position;
layout(location = 1) in  vec3 in_Color;
layout(location = 2) in  vec3 in_Normal;
layout(location = 3) in  float in_idHueso;
layout(location = 4) in  float in_peso;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat4 normalMatrix;
uniform vec3 vecVista;

/**Esqueleto**/
uniform mat4 poseMatrix[%nhuesos%];
uniform mat4 bindPose[%nhuesos%];
uniform vec3 colores[%nhuesos%];
uniform mat4 bindPoseInv[%nhuesos%];
uniform mat4 boneTransforms[%nhuesos%];
uniform mat4 normalBone[%nhuesos%];

/**iluminacion*/
out vec3 vertex_normal;
out vec3 luz; 
// Salida
out vec3 ex_Color;
out vec3 ex_vecVista;
void main(void) {
    int idHueso=int(in_idHueso);
    vertex_normal=normalize(mat3(normalBone[idHueso])*in_Normal);
    vec4 pos=modelMatrix*boneTransforms[idHueso]*vec4(in_Position+normalize(in_Normal)*0.02,1.0);
//    pos=modelMatrix*vec4(in_Position,1.0);

    gl_Position = projectionMatrix*viewMatrix*(pos);
//    gl_Position = projectionMatrix*viewMatrix*modelMatrix*vec4(in_Position,1.0);

   luz=normalize(vec3(0.4,-0.4,1.0));
    
   ex_vecVista=vec3(inverse(viewMatrix)*vec4(0.0,0.0,0.0,1.0)-pos);
   ex_Color = in_Color*0.3;
}
