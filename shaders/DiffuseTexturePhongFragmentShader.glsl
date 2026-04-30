#version 450 core
out vec4 FragColour;

in vec3 fragPos;
// in vec3 vertexCol;
in vec3 fragNormal;
in vec2 fragTexCoord;

uniform vec3 lightPos;
uniform vec3 cameraViewPos;
uniform vec3 ambientLight = vec3(0.1, 0.1, 0.1);
uniform vec3 specularColour = vec3(0.5, 0.5, 0.5);
float specularStrength = 1.0;

uniform vec3 lightColour = vec3(0.95, 0.95, 0.95);

uniform sampler2D diffuseTexture;
uniform sampler2D metallicTexture;
uniform sampler2D normalTexture;
uniform sampler2D roughnessTexture;

void main() {
    vec3 normal = normalize(fragNormal);
    vec3 lightDir = normalize(lightPos - fragPos);
    vec3 viewDir = normalize(cameraViewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float dist = distance(lightPos, fragPos);

    vec3 diffuseColour = texture(diffuseTexture, fragTexCoord).xyz;
    float diffuseStrength = max(dot(normal, lightDir), 0.0);
    vec3 diffuseLight = diffuseColour * diffuseStrength * lightColour;

    float specularStrength = pow(max(dot(viewDir, reflectDir), 0.0), 16.0);
    vec3 specularLight = specularColour * specularStrength * lightColour;

    vec3 result = diffuseLight + ambientLight + specularLight;

    FragColour = vec4(result, 1.0);
}