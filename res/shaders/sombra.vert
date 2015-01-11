#version 330
// in_Position was bound to attribute index 0 and in_Color was bound to attribute index 1
layout(location = 0) in  vec3 in_Position;
layout(location = 1) in  vec3 in_Color;
layout(location = 2) in  vec3 in_Normal;
layout(location = 3) in  float in_idHueso;
layout(location = 4) in  float in_peso;
layout(location = 5) in  float in_uv;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 viewMatrixInv;
uniform mat4 modelMatrix;
uniform mat4 normalMatrix;
uniform vec3 vecVista;

out vec3 ex_color;

void main(void) {
    vec4 pos=modelMatrix*vec4(in_Position, 1.0);
    gl_Position = projectionMatrix*viewMatrix*pos;
    ex_color=in_Color;
}
