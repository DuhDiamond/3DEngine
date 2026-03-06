#version 450 core
out vec4 FragColour;
in vec3 aPosColour;

void main() {
    FragColour = vec4(aPosColour, 1.0);
}