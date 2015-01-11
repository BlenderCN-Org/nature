#version 330
// It was expressed that some drivers required this next line to function properly
precision highp float;

in vec3 ex_color;
layout(location = 0) out float fragmentdepth;
layout(location = 1) out vec4 out_color;
void main(void) {
//    fragmentdepth = gl_FragCoord.z;
    fragmentdepth = gl_FragCoord.z;
//    out_color=vec4(0.52,0.52,0.52,0.52)*gl_FragCoord.z;
    out_color=vec4(ex_color,1);
}
