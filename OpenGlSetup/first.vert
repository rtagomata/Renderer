#version 140

in vec3 inputPosition;
in vec4 inputColor;

out vec3 forFragColor;

void main(){
    // Calculate grayscale value using the luminance formula
    float grayscale = dot(inputColor.rgb, vec3(0.299, 0.587, 0.114));

    // Set forFragColor to grayscale
    forFragColor = vec3(grayscale);

    gl_Position = vec4(inputPosition, 1.0);
}