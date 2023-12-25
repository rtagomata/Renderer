#version 140
 
in vec3 forFragColor;
out vec4 outputColor;
 
void main() {
    outputColor = vec4(forFragColor,1.0);
}
