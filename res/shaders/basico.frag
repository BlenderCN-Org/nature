#version 330
// It was expressed that some drivers required this next line to function properly
precision highp float;

in  vec3 ex_Color;

out vec4 out_color;
in vec3 vertex_normal;
in vec3 vertex_light_position;


void main(void) {
    // Pass through our original color with full opacity.
    vec4 ambient_color= vec4(0.1,0.1,0.12,1.0);
    float diffuse_value = clamp(dot(normalize(vertex_normal), normalize(vertex_light_position)), 0,1);

    //float specular_value=max(1.0-max(dot(vertex_normal, vertex_light_position), 0.0),0.3);
    //float specular_value=max(1.0-max(dot(vertex_normal, vertex_light_position), 0.0),0.3);
    vec4 c1=ambient_color+(vec4(1,1,1,1.0)*diffuse_value);
    out_color=c1;    //out_color=vec4(vertex_normal,1.0);

   // if(diffuse_value>0.5){
    //  out_color=vec4(1.0,0.0,0.0,1.0);
    //}else{
    //  out_color=vec4(0.0,1.0,0.0,1.0);
    //}
    //out_color=vec4(1.0,1.0,1.0,1.0)*diffuse_value;
    //*****Toon
    out_color=vec4(ex_Color,1.0)+ambient_color*diffuse_value;
   //vec3 n_Color=vec3(0.2,0.6,0.8);
   //diffuse_value = clamp(dot(vertex_normal, normalize(vertex_light_position)), 0.0,1.0)*0.7;
   //if (diffuse_value > 0.15){
     // out_color=vec4(ex_Color,1.0)+ambient_color;
   //}else
   if (diffuse_value > 0.3){
      out_color=vec4(ex_Color,1.0)*0.8+ambient_color;
   }else{
      out_color=vec4(ex_Color,1.0)*0.6+ambient_color;
   }
   //out_color=vec4(ex_Color,1.0)*0.6+ambient_color;
}
