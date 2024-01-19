#version 140
 
layout(location = 0) in vec3 inputPosition;
layout(location = 1) in vec3 inputNormal;
 
out vec3 outNormal;
 
void main(){


    gl_Position = vec4(inputPosition, 1.0);
    outNormal = inputNormal;
}
