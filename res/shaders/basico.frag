#version 330
// It was expressed that some drivers required this next line to function properly
precision highp float;

in  vec3 ex_Color;

out vec4 out_color;
in vec3 vertex_normal;
in vec3 ex_luz;
in vec3 ex_vecVista;
in vec3 shadowPos;

uniform  sampler2DShadow shadowMap;


void main(void) {
   vec4 ambient_color= vec4(0.1,0.1,0.12,1.0);
   float diffuse_value = clamp(dot(normalize(vertex_normal), normalize(ex_luz)),0,1);
   float view_value = dot(normalize(ex_vecVista),normalize(vertex_normal));
   float bias = 0.005*tan(acos(diffuse_value));
   bias = clamp(bias,0,0.01f);
   float esshadow=texture(shadowMap,vec3(shadowPos.xy,shadowPos.z-bias));
   float shadow_value=0.8;  
   if(esshadow==0){
       shadow_value=0.6;
   }
   out_color=vec4(ex_Color,1.0)*shadow_value+ambient_color;
    out_color=vec4(ex_Color,1.0)*0.4+vec4(ex_Color,1.0)*diffuse_value*shadow_value+ambient_color;
//   out_color=vec4(ex_Color,1.0)*0.4+vec4(ex_Color,1.0)*0.6*diffuse_value+ambient_color;
   
//   out_color=vec4(1,0,0,1)*shadow_value;
   if(view_value>0.999){
   }
}
