
#version 140
#extension GL_ARB_explicit_attrib_location : enable
 
layout(location = 0) in vec3 inputPosition;
layout(location = 1) in vec3 inputNormal;
 
out vec3 outNormal;
 
void main(){


    gl_Position = vec4(inputPosition.x + 100, inputPosition.y, inputPosition.z, 1.0);
    outNormal = inputNormal;
}
