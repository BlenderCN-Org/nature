#version 100
precision mediump float;

varying vec3 ex_Color;
varying vec3 vertex_normal;
varying vec3 luz;
varying vec3 ex_vecVista;


void main(void) {
   vec4 ambient_color= vec4(0.1,0.1,0.12,1.0);
   float diffuse_value = max(dot(normalize(vertex_normal), normalize(luz)), 0.0);
   float view_value = dot(normalize(ex_vecVista),normalize(vertex_normal));
   if (diffuse_value > 0.3){
      gl_FragColor=vec4(ex_Color,1.0)*0.8+ambient_color;
   }else{
      gl_FragColor=vec4(ex_Color,1.0)*0.6+ambient_color;
   }

}
