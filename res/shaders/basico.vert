#version 100
// in_Position was bound to attribute index 0 and in_Color was bound to attribute index 1
attribute  vec3 in_Position;
attribute  vec3 in_Color;
attribute  vec3 in_Normal;
attribute  float in_idHueso;
attribute  float in_peso;
attribute  vec2 in_uv;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 luzMatrix;
uniform mat4 viewMatrixInv;
uniform mat4 modelMatrix;
uniform mat4 normalMatrix;
uniform vec3 vecVista;
uniform vec3 luz;
// We output the ex_Color variable to the next shader in the chain
varying vec3 ex_Color;
varying vec3 vertex_normal;
varying vec3 ex_luz;
varying vec2 uv;
varying vec3 ex_vecVista;
varying vec3 shadowPos;



void main(void) {
    vec4 pos=modelMatrix*vec4(in_Position, 1.0);
    gl_Position = projectionMatrix*viewMatrix*pos;
    shadowPos=(luzMatrix*pos).xyz;
    vertex_normal=normalize(mat3(normalMatrix)*in_Normal);
    ex_luz=(viewMatrix*vec4(luz,0.0)).xyz;
    ex_luz=luz;
    uv=in_uv;
    ex_Color = in_Color;
    ex_vecVista=vec3(viewMatrixInv*vec4(0.0,0.0,0.0,1.0)-pos);
}
