#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <glad/glad.h>
#include <vector>

#include "Mesh/Mesh.hpp"
#include "Material/Material.hpp"
#include "ObjectInstance.hpp"

using namespace std;

// Class that holds a fully loaded Object to be instanced
class Object {
private:
    Mesh *objectMesh = nullptr;
    Material *objectMaterial = nullptr;
public:
    // Holds all the instances for this specific object
    vector<ObjectInstance> instances = vector<ObjectInstance>();

    // Constructor which takes in loaded data to create this object
    Object(Mesh *mesh, Material *material);
    Object(Mesh *mesh);

    // Calls Draw() on every object instance in instances
    void DrawAll();

    // Creates an instance with an associated VBO through the OpenGL API and returns the corresponding ID for it
    void CreateInstance(float scale, float location[3]);

    ~Object();
};

class ObjectInstance {
private:
    // Pointer which holds the associated ID for the instance's buffered data
    unsigned int *VBO_ID = nullptr;
    // This will hold this object's data in the format that OpenGL's pipeline expects in a dynamic array
    float *objBuffer = nullptr;
public:
    // When an instance is created from ObjectFactory, this constructor should set it up via the OpenGL API
    ObjectInstance();
    // Draws this object instance to the screen
    void Draw();
};

#endif