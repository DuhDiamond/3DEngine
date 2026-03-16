#version 450 core
out vec4 FragColour;
in vec3 vertexCol;

void main() {
    FragColour = vec4(vertexCol, 1.0);
}