#version 140
 
in vec3 inPosition;
out vec3 outputPosition;
 
void main() {
    outputPosition = vec3(inPosition.x + 1.0, inPosition.y, inPosition.z);

    gl_Position = outputPosition;
}
