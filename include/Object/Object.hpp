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
class Object
{
private:
    ObjMesh *objectMesh = nullptr;
    PBRMaterial *objectMaterial = nullptr;

    // Scale defaults to (1, 1, 1)
    glm::mat4 scale = glm::mat4(1.0f);

    // Note for future: Works for now, but this method may suffer from gimbal lock
    // Look into alternatives (e.g., quaternions)
    glm::mat4 rotation = glm::mat4(1.0f);

    // Position defaults to (0, 0, 0)
    glm::mat4 position = glm::mat4(1.0f);

    // Note: this is matrix multiplication (right-to-left)
    void recomputeModelMatrix();

    unsigned int getVAO_ID();
    unsigned int getVBO_ID();

public:
    // Methods to attach things through openGL, and if relevant, register it through OpenGL
    void Attach(ObjMesh *mesh);
    void Attach(PBRMaterial *material);

    void useShader();

    // Builds the buffer for this object and displays it
    void Instantiate();
    
    unsigned int getShader_ID();

    void Draw();

    // These methods are held seperately from the actual values,
    // as each time one of these methods are called, the corresponding attribute in the OpenGL
    // buffer will also need to be changed
    void SetSize(float xSize, float ySize, float zSize);
    void SetPosition(float x, float y, float z);
    // Still need to figure out a better solution for this i.e. gimbal lock
    void SetRotation(float xAngle, float yAngle, float zAngle);

    void Scale(float xScale, float yScale, float zScale);
    void Translate(float xTranslate, float yTranslate, float zTranslate);
    // Still need to figure out a better solution for this i.e. gimbal lock
    void Rotate(float xAngle, float yAngle, float zAngle);

    /*
    glm::vec3 GetScale();
    glm::vec3 GetPosition();
    glm::vec3 GetRotation();
    */
};

#endif