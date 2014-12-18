#version 100 
// It was expressed that some drivers required this next line to function properly
precision mediump float;

varying vec3 ex_Color;


void main(void) {
  gl_FragColor=vec4(ex_Color,1.0);
}
