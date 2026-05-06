#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Object/Object.hpp"
#include "Object/ObjMesh.hpp"
#include "Scene/Clock.hpp"

void Object::recomputeModelMatrix()
{
    instanceInfo.modelMatrix = position * rotation * scale;
    objectMaterial->updateModelMatrix(instanceInfo.modelMatrix);
}

void Object::Attach(ObjMesh *mesh)
{
    objectMesh = mesh;
    mesh->incrementInstanceCount();
}

void Object::Attach(PBRMaterial *material) { objectMaterial = material; }
void Object::useShader() { objectMaterial->useShader(); }
unsigned int Object::getVAO_ID() { return objectMesh->getVAO_ID(); }
unsigned int Object::getShader_ID() { return objectMaterial->getShader_ID(); }
unsigned int Object::getVBO_ID() { return objectMesh->getVBO_ID(); }

void Object::Draw()
{
    // Note for later: Look into using bindMeshVAO() only when drawing
    // a different set of instances for a given ObjMesh, otherwise binding VBO is the way to go
    objectMesh->bindMeshVAO();
    objectMaterial->bindAllMaps();
    recomputeModelMatrix();
    glDrawElements(GL_TRIANGLES, objectMesh->EBOBuffer.size(), GL_UNSIGNED_INT, 0);
}

void Object::SetSize(float xSize, float ySize, float zSize)
{
    scale = glm::scale(glm::mat4(1.0), glm::vec3(xSize, ySize, zSize));
    recomputeModelMatrix();
}
void Object::SetPosition(float x, float y, float z)
{
    position = glm::translate(glm::mat4(1.0), glm::vec3(x, y, z));
    recomputeModelMatrix();
}
void Object::SetRotation(float xAngle, float yAngle, float zAngle)
{
    rotation = glm::mat4(1.0f);
    // For now i'm rotating by x, then y, and then z
    // Eventually this will be replaced with a better system entirely
    rotation = glm::rotate(rotation, glm::radians(xAngle), glm::vec3(1, 0, 0));
    rotation = glm::rotate(rotation, glm::radians(yAngle), glm::vec3(0, 1, 0));
    rotation = glm::rotate(rotation, glm::radians(zAngle), glm::vec3(0, 0, 1));

    recomputeModelMatrix();
}

void Object::Scale(float xScale, float yScale, float zScale)
{
    scale = glm::scale(scale, glm::vec3(xScale, yScale, zScale));
    recomputeModelMatrix();
}
void Object::Translate(float xTranslate, float yTranslate, float zTranslate)
{
    position = glm::translate(position, glm::vec3(xTranslate, yTranslate, zTranslate));
    recomputeModelMatrix();
}
void Object::Rotate(float xAngle, float yAngle, float zAngle)
{
    rotation = glm::rotate(rotation, glm::radians(xAngle), glm::vec3(1, 0, 0));
    rotation = glm::rotate(rotation, glm::radians(yAngle), glm::vec3(0, 1, 0));
    rotation = glm::rotate(rotation, glm::radians(zAngle), glm::vec3(0, 0, 1));
    recomputeModelMatrix();
}