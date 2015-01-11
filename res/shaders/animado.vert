#version 330
// atributos
layout(location = 0) in  vec3 in_Position;
layout(location = 1) in  vec3 in_Color;
layout(location = 2) in  vec3 in_Normal;
layout(location = 3) in  float in_idHueso;
layout(location = 4) in  float in_peso;
layout(location = 5) in  vec2 in_uv;

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
out vec3 ex_Color;
out vec3 vertex_normal;
out vec3 ex_luz; 
// Salida
out vec2 uv;
out vec3 ex_vecVista;
out vec3 shadowPos;

void main(void) {
    int idHueso=int(in_idHueso);
    vec4 pos=modelMatrix*boneTransforms[idHueso]*vec4(in_Position,1.0);
    gl_Position = projectionMatrix*viewMatrix*pos;
    shadowPos=(luzMatrix*pos).xyz;
    vertex_normal=normalize(mat3(normalBone[idHueso])*in_Normal);
    ex_vecVista=vec3(viewMatrixInv*vec4(0.0,0.0,0.0,1.0)-pos);
    ex_luz=(viewMatrix*vec4(luz,1)).xyz;
    ex_luz=luz;
    uv=in_uv;
    ex_Color = in_Color;
}
