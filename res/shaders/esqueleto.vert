#version 330
// in_Position was bound to attribute index 0 and in_Color was bound to attribute index 1
layout(location = 0) in  vec3 in_Position;
layout(location = 1) in  float esCabeza;
layout(location = 2) in  float _idHueso;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat4 normalMatrix;
uniform mat4 poseMatrix[6];
uniform mat4 bindPose[6];
uniform vec3 colores[6];

/**Salida**/
out vec3 ex_Color;



void main(void) {
    int idHueso=int(_idHueso);
    vec4 position=poseMatrix[idHueso]*inverse(bindPose[idHueso])*vec4(in_Position,1.0);
    gl_Position = projectionMatrix*viewMatrix*modelMatrix*bindPose[idHueso]*position;

//    gl_Position = projectionMatrix*viewMatrix*modelMatrix*bindPose[idHueso]*vec4(in_Position,1.0f);
    if(esCabeza!=0){
        ex_Color = vec3(0.1,0.1,0.10);
        ex_Color = colores[idHueso];
    }else{
        ex_Color = vec3(0.4,0.7,0.82);
        ex_Color = colores[idHueso]*0.1;
    }
}
