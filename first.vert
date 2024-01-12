#version 140
 
in vec3 inputPosition;
in vec3 inputNormal;
 
out vec3 inputPosition;
 
void main(){


    gl_Position = vec4(inputPosition, 1.0);
}
