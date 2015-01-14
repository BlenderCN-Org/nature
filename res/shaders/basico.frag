#version 130
// It was expressed that some drivers required this next line to function properly
precision mediump float;

varying  vec3 ex_Color;


varying vec3 vertex_normal;
varying vec3 ex_luz;
varying vec3 ex_uv;
varying vec4 ex_oclu;
varying vec3 ex_vecVista;
varying vec3 shadowPos;

uniform  sampler2DShadow shadowMap;
//uniform  sampler2D shadowMap;


void main(void) {
   vec4 out_color;
   vec4 ambient_color=vec4(0.1,0.1,0.12,1.0);
   float diffuse_value = max(dot(normalize(vertex_normal), normalize(ex_luz)),0.0);
   float view_value = dot(normalize(ex_vecVista),normalize(vertex_normal));
   float bias = 0.005*tan(acos(diffuse_value));
    bias = 0.005;
//   bias = max(min(bias,0.01),0.0);
   //float esshadow=texture(shadowMap,vec3(shadowPos.xy,shadowPos.z-bias));
    bool esshadow=texture(shadowMap,vec3(shadowPos.xy,shadowPos.z-bias))==0;
   //bool esshadow=texture2D(shadowMap,shadowPos.xy).z<=(shadowPos.z-bias);
//   float esshadow=1.0;
   float shadow_value=0.8;  
   if(diffuse_value<0.3||esshadow){
       shadow_value=0.6;
   }
   float oclu_value=1-ex_oclu.w*abs(dot(normalize(ex_oclu.xyz),normalize(vertex_normal)));
   oclu_value=1.0-ex_oclu.w*1.0;
   out_color=vec4(ex_Color,1.0)*shadow_value*oclu_value+ambient_color;

   gl_FragColor=out_color;
}
