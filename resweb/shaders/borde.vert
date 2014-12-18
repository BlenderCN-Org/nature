#version 100

// in_Position was bound to attribute index 0 and in_Color was bound to attribute index 1
attribute  vec3 in_Position;
attribute vec3 in_Color;
attribute  vec3 in_Normal;
attribute  float in_idHueso;
attribute  float in_peso;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat4 normalMatrix;
uniform vec3 vecVista;
// We output the ex_Color variable to the next shader in the chain
varying vec3 ex_Color;
varying vec3 vertex_normal;
varying vec3 luz;
varying vec3 ex_vecVista;



void main(void) {
    vec4 pos=modelMatrix*vec4(in_Position+normalize(in_Normal)*0.02, 1.0);
    gl_Position = projectionMatrix*viewMatrix*(pos);
    vertex_normal=normalize(mat3(normalMatrix)*in_Normal);
    luz=normalize(vec3(0.4,-0.4,1.0));
    ex_Color = in_Color*0.3;
    ex_vecVista=vec3(viewMatrix*vec4(0.0,0.0,0.0,1.0)-pos);
}
