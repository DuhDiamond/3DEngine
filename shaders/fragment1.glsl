#version 450 core
out vec4 FragColour;

in vec3 vertexCol;
in vec3 vertexNormal;
in vec2 vertexTexCoord;

uniform sampler2D objTexture;

void main() {

    // Multiplying the vertex colour by each vertex normal so you can
    // see elements of both in the output
    FragColour = vec4(abs(vertexCol * vertexNormal), 1.0);

    // Trying to troubleshoot texture still;
    // loading works, but does not align texture as expected
    // FragColour = texture(objTexture, vertexTexCoord);
}