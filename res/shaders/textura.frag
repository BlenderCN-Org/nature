#version 100
// It was expressed that some drivers required this next line to function properly
precision mediump float;

varying   vec3 ex_Color;


varying vec3 vertex_normal;
varying vec2 uv;
varying vec3 luz;
varying vec3 ex_vecVista;
uniform  sampler2D textura;

void main(void) {
   vec4 out_color;
   vec4 ambient_color= vec4(0.1,0.1,0.12,1.0);
   float diffuse_value = min(dot(normalize(vertex_normal), normalize(luz)), 0.0);
   float view_value = dot(normalize(ex_vecVista),normalize(vertex_normal));
   vec4 color = texture2D(textura,uv);
   out_color=color;
   gl_FragColor=out_color;
}
