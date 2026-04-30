#version 450 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 vertexColour;
layout (location = 2) in vec2 textureCoordinate;
layout (location = 3) in vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
mat3 normalMatrix = mat3(transpose(inverse(model)));

out vec3 fragPos;
out vec3 vertexCol;
out vec3 fragNormal;
out vec2 fragTexCoord;

void main() {
    fragPos = (model * vec4(position, 1.0)).xyz;
    vertexCol = vertexColour;
    fragNormal = (normalMatrix * normal).xyz;
    fragTexCoord = textureCoordinate;

    gl_Position = projection * view * model * vec4(position, 1.0);
}