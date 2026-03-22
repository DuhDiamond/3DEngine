#version 450 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 vertexColour;
layout (location = 2) in vec2 textureCoordinate;
layout (location = 3) in vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 lightPosition;

out vec3 vertexPos;
out vec3 vertexCol;
out vec3 vertexNormal;
out vec2 vertexTexCoord;

out vec3 lightPos;

mat4 normalMatrix = transpose(inverse(model));

void main() {
    vertexPos = vec3(model * vec4(position, 1.0));
    vertexCol = vertexColour;
    vertexTexCoord = textureCoordinate;
    vertexNormal = normalize(vec3(normalMatrix * vec4(normal, 1.0)));

    lightPos = vec3(25, 15, -15);

    gl_Position = projection * view * model * vec4(position, 1.0);
}