#version 120
// atributos
attribute  vec3 in_Position;
attribute  vec3 in_Color;
attribute  vec3 in_Normal;
attribute  float in_idHueso;
attribute  float in_peso;
attribute  vec2 in_uv;
attribute  vec4 in_oclu;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 luzMatrix;
uniform mat4 viewMatrixInv;
uniform mat4 modelMatrix;
uniform mat4 normalMatrix;
uniform vec3 vecVista;
uniform vec3 luz;

/**Esqueleto**/
uniform mat4 poseMatrix[%nhuesos%];
uniform mat4 bindPose[%nhuesos%];
uniform vec3 colores[%nhuesos%];
uniform mat4 bindPoseInv[%nhuesos%];
uniform mat4 boneTransforms[%nhuesos%];
uniform mat4 normalBone[%nhuesos%];

/**iluminacion*/
varying vec3 ex_Color;
varying vec3 vertex_normal;
varying vec3 ex_luz; 
// Salida
varying vec2 ex_uv;
varying vec3 ex_vecVista;
varying vec3 shadowPos;

varying vec4 ex_oclu;
void main(void) {
    int idHueso=int(in_idHueso);
    vec4 pos=modelMatrix*boneTransforms[idHueso]*vec4(in_Position,1.0);
    gl_Position = projectionMatrix*viewMatrix*pos;
    shadowPos=(luzMatrix*pos).xyz;
    vertex_normal=normalize(mat3(normalBone[idHueso])*in_Normal);
    ex_vecVista=vec3(viewMatrixInv*vec4(0.0,0.0,0.0,1.0)-pos);
    ex_luz=(viewMatrix*vec4(luz,1)).xyz;
    ex_luz=luz;
    ex_uv=in_uv;
    ex_oclu=in_oclu;
    ex_Color = in_Color;
}
