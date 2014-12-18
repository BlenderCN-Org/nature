#version 330
// It was expressed that some drivers required this next line to function properly
precision highp float;

in  vec3 ex_Color;

out vec4 out_color;
in vec3 vertex_normal;
in vec3 luz;
in vec3 ex_vecVista;


void main(void) {
   vec4 ambient_color= vec4(0.1,0.1,0.12,1.0);
   float diffuse_value = clamp(dot(normalize(vertex_normal), normalize(luz)), 0,1);
   float view_value = dot(normalize(ex_vecVista),normalize(vertex_normal));
   if (diffuse_value > 0.3){
      out_color=vec4(ex_Color,1.0)*0.8+ambient_color;
   }else{
      out_color=vec4(ex_Color,1.0)*0.6+ambient_color;
   }
//   out_color=vec4(ex_Color,1.0f)*0.8+ambient_color;
   if(view_value>0.999){
   }
}
