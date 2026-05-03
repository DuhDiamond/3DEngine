#version 450 core
out vec4 FragColour;

in vec3 fragPos;
in vec3 vertexCol;
in vec3 fragNormal;
in vec2 fragTexCoord;

uniform vec3 cameraViewPos;
uniform vec3 ambientLight = vec3(0.1, 0.1, 0.1);
uniform vec3 specularColour = vec3(0.5, 0.5, 0.5);
float specularStrength = 1.0;

struct pointlight {
    vec3 pos;
    vec3 colour;
};

#define NUM_POINTLIGHTS 2
uniform pointlight pointlights[NUM_POINTLIGHTS];

vec3 calculatePointLight(pointlight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 diffuseColour) {
    vec3 contribution = vec3(0.0, 0.0, 0.0);
    vec3 lightDir = normalize(light.pos - fragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float dist = distance(light.pos, fragPos);

    float falloff = 1.0/(dist * dist);

    float diffuseStrength = max(dot(normal, lightDir), 0.0);
    vec3 diffuseLight = diffuseColour * diffuseStrength * light.colour;
    contribution += falloff * diffuseLight;

    float specularStrength = pow(max(dot(viewDir, reflectDir), 0.0), 16.0);
    vec3 specularLight = specularColour * specularStrength * light.colour;
    contribution += falloff * specularLight;

    return contribution;
}

void main() {
    vec3 normal = normalize(fragNormal);
    vec3 viewDir = normalize(cameraViewPos - fragPos);
    vec3 diffuseColour = vertexCol;

    vec3 result = vec3(0.0, 0.0, 0.0);
    result += ambientLight;

    for (int i = 0; i < NUM_POINTLIGHTS; i++) {
        result += calculatePointLight(pointlights[i], normal, fragPos, viewDir, diffuseColour);
    }

    FragColour = vec4(result, 1.0);
}