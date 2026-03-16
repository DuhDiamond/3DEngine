#include "Object/Object.hpp"
#include "Object/ObjMesh.hpp"

void Object::Instantiate() {

    unsigned int instanceVBO_ID;
    float *buffer = objectMesh->getBuffer();

    glBindVertexArray(objectMesh->getVAO_ID());
    glGenBuffers(1, &instanceVBO_ID);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO_ID);
    glBufferData(GL_ARRAY_BUFFER, objectMesh->getBufferSize()*sizeof(float), buffer, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11*sizeof(float), (void*)0);
    
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11*sizeof(float), (void*)(3*sizeof(float)));
    
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11*sizeof(float), (void*)(7*sizeof(float)));
    
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11*sizeof(float), (void*)(10*sizeof(float)));

    glBindVertexArray(0);

    VBO_ID = instanceVBO_ID;
}

void Object::Attach(ObjMesh *mesh) {
    objectMesh = mesh;
}

void Object::Attach(IMaterial *material) {
    objectMaterial = material;
}

void Object::Attach(shader *shader) {
    materialShader = shader;
}

void Object::useShader() {
    materialShader->use();
}

unsigned int Object::getVAO_ID() {
    return objectMesh->getVAO_ID();
}

unsigned int Object::getShaderID() {
    return materialShader->getShaderID();
}

unsigned int Object::getVBO_ID() {
    return VBO_ID;
}

Object::~Object() {

}