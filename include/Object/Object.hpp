#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <glad/glad.h>
#include <vector>

#include "IMesh.hpp"
#include "ObjMesh.hpp"
#include "IMaterial.hpp"
#include "PBRMaterial.hpp"

using namespace std;

// Class that holds a fully loaded Object to be instanced

// This is held for each Object that shares the same mesh
// (IndirectRender will sort these out and combine them per-instance)
struct perInstanceObjectBuffer {
    glm::mat4 modelMatrix;
};

class Object
{
private:
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 rotation = glm::mat4(1.0f);
    glm::mat4 position = glm::mat4(1.0f);

    perInstanceObjectBuffer instanceInfo;

    void recomputeModelMatrix();

    unsigned int getVAO_ID();
    unsigned int getVBO_ID();

public:
    ObjMesh *objectMesh = nullptr;
    PBRMaterial *objectMaterial = nullptr;

    // Methods to attach things through OpenGL, and if relevant, register it through OpenGL
    void Attach(ObjMesh *mesh);
    void Attach(PBRMaterial *material);

    void useShader();
    
    unsigned int getShader_ID();

    void Draw();

    void SetSize(float xSize, float ySize, float zSize);
    void SetPosition(float x, float y, float z);
    void SetRotation(float xAngle, float yAngle, float zAngle);

    void Scale(float xScale, float yScale, float zScale);
    void Translate(float xTranslate, float yTranslate, float zTranslate);
    void Rotate(float xAngle, float yAngle, float zAngle);
};

#endif