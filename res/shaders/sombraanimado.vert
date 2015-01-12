#version 100
// in_Position was bound to attribute index 0 and in_Color was bound to attribute index 1
attribute  vec3 in_Position;
attribute  vec3 in_Color;
attribute  vec3 in_Normal;
attribute  float in_idHueso;
attribute  float in_peso;
attribute  float in_uv;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 viewMatrixInv;
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

varying vec3 ex_color;

void main(void) {
    int idHueso=int(in_idHueso);
    vec4 pos=modelMatrix*boneTransforms[idHueso]*vec4(in_Position,1.0);
    gl_Position = projectionMatrix*viewMatrix*pos;
    ex_color=in_Color;
}
