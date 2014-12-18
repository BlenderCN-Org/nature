#version 100 
// atributos
attribute  vec3 in_Position;
attribute  vec3 in_Color;
attribute  vec3 in_Normal;
attribute  float in_idHueso;
attribute  float in_peso;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat4 normalMatrix;
uniform vec3 vecVista;

/**Esqueleto**/
uniform mat4 poseMatrix[6];
uniform mat4 bindPose[6];
uniform vec3 colores[6];
uniform mat4 bindPoseInv[6];
uniform mat4 boneTransforms[6];
uniform mat4 normalBone[6];



/**iluminacion*/
varying vec3 vertex_normal;
varying vec3 luz;
// Salida
varying vec3 ex_Color;
varying vec3 ex_vecVista;

void main(void) {
    int idHueso=int(in_idHueso);
    vec4 pos=modelMatrix*boneTransforms[idHueso]*vec4(in_Position,1.0);
    gl_Position = projectionMatrix*viewMatrix*pos;
    vertex_normal=normalize(mat3(normalMatrix)*in_Normal);
    luz=normalize(vec3(0.4,-0.4,1.0));
    ex_vecVista=vec3(viewMatrix*vec4(0.0,0.0,0.0,1.0)-pos);
    ex_Color = in_Color;
}
