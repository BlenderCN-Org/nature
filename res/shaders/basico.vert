#version 330
// in_Position was bound to attribute index 0 and in_Color was bound to attribute index 1
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
// We output the ex_Color variable to the next shader in the chain
out vec3 ex_Color;
out vec3 vertex_normal;
out vec3 luz;
out vec3 ex_vecVista;



void main(void) {
    vec4 pos=modelMatrix*vec4(in_Position, 1.0);
    gl_Position = projectionMatrix*viewMatrix*pos;
    vertex_normal=normalize(mat3(normalMatrix)*in_Normal);
    luz=normalize(vec3(0.4,-0.4,1.0));
    ex_Color = in_Color;
    ex_vecVista=vec3(inverse(viewMatrix)*vec4(0.0,0.0,0.0,1.0)-pos);
}