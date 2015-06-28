#version 100
precision mediump float;

varying  vec3 ex_Color;
varying vec3 vertex_normal;
varying vec3 ex_luz;
varying vec2 ex_uv;
varying vec4 ex_oclu;
varying vec3 ex_vecVista;
varying vec3 shadowPos;



void main(void) {
   vec4 out_color;
   vec4 ambient_color=vec4(0.1,0.1,0.12,1.0);
   float diffuse_value = max(dot(normalize(vertex_normal), normalize(ex_luz)),0.0);
   float view_value = dot(normalize(ex_vecVista),normalize(vertex_normal));
   float shadow_value=0.8;  
   if(diffuse_value<0.3){
       shadow_value=0.6;
   }
   float oclu_value=1.0-ex_oclu.w*abs(dot(normalize(ex_oclu.xyz),normalize(vertex_normal)));
   oclu_value=1.0-ex_oclu.w*ex_oclu.w*0.5;
   out_color=vec4(ex_Color,1.0)*shadow_value*oclu_value+ambient_color;

   gl_FragColor=out_color;
}
