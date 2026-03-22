#version 450 core
out vec4 FragColour;

in vec3 vertexPos;
in vec3 vertexCol;
in vec3 vertexNormal;
in vec2 vertexTexCoord;

in vec3 lightPos;

uniform vec3 ambient = vec3(0.25, 0.25, 0.25);
uniform vec3 colour = vec3(1.0, 1.0, 1.0);
// To be changed later as passed in via position of camera class
// Currently I just assume camera is at (0, 0, 0)
// Also, for the specular calculation, perhaps camera angle also
// needs to be taken into account?
uniform vec3 viewPos = vec3(0, 0, 0);
float specularStrength = 1.0;

uniform vec3 lightColour = vec3(0.95, 0.95, 0.95);

uniform sampler2D objTexture;

void main() {
    vec3 lightDir = normalize(vertexPos - lightPos);
    
    float diff = max(dot(vertexNormal, lightDir), 0.0);
    vec3 diffuse = diff * lightColour;
    vec3 viewDir = normalize(viewPos - vertexPos);
    vec3 reflectDir = reflect(-lightDir, vertexNormal);

    vec4 diffuseTexture = texture(objTexture, vertexTexCoord);


    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColour;

    vec3 result = (diffuse + ambient + specular) * vec3(diffuseTexture);


    FragColour = vec4(result, 1.0);
    // FragColour = texture(objTexture, vertexTexCoord);
}