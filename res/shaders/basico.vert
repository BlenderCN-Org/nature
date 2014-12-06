#version 330
// in_Position was bound to attribute index 0 and in_Color was bound to attribute index 1
layout(location = 0) in  vec3 in_Position;
layout(location = 1) in  vec3 in_Color;
layout(location = 2) in  vec3 in_Normal;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat4 normalMatrix;
// We output the ex_Color variable to the next shader in the chain
out vec3 ex_Color;
out vec3 vertex_normal;
out vec3 vertex_light_position;



void main(void) {


    gl_Position = projectionMatrix*viewMatrix*modelMatrix*vec4(in_Position, 1.0);

    vertex_normal=normalize(mat3(normalMatrix)*in_Normal);
    //vertex_normal=in_Normal;

    vertex_light_position=normalize(vec3(0.4,-0.4,1.0));

    //gl_Normal=in_Normal;
    // GLSL allows shorthand use of vectors too, the following is also valid:
    // gl_Position = vec4(in_Position, 0.0, 1.0);
    // We're simply passing the color through unmodified

    ex_Color = in_Color;
}
