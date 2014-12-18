#version 330
// It was expressed that some drivers required this next line to function properly
precision highp float;

in  vec3 ex_Color;
out vec4 out_color;


void main(void) {
out_color=vec4(ex_Color,1.0);
}
