#version 330 core

in vec3 fragNormal;

out vec4 fragColor;

void main() {
    // Use the normal for simple color representation (for illustration)
    fragColor = vec4(normalize(fragNormal) * 0.5 + 0.5, 1.0);
}