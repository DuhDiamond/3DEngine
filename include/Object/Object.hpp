#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <glad/glad.h>
#include <vector>

#include "IMesh.hpp"
#include "ObjMesh.hpp"
#include "IMaterial.hpp"

using namespace std;

// Class that holds a fully loaded Object to be instanced
class Object
{
private:
    ObjMesh *objectMesh = nullptr;
    IMaterial *objectMaterial = nullptr;
    shader *materialShader = nullptr;

    // Pointer which holds the associated ID for the instance's buffered data
    unsigned int VBO_ID;

    // Scale defaults to (1, 1, 1)
    struct scale {
        float x = 0;
        float y = 0;
        float z = 0;
    };

    // Position defaults to (0, 0, 0)
    struct position {
        float x = 0;
        float y = 0;
        float z = 0;
    };

    // Note for future: Works for now, but this method suffers from gimbal lock
    // Look into alternatives (e.g., quaternions)
    struct rotation {
        float x = 0;
        float y = 0;
        float z = 0;
    };

public:
    // These methods are held seperately from the actual values,
    // as each time one of these methods are called, the corresponding attribute in the OpenGL
    // buffer will also need to be changed
    struct SetScale {
        void x(float x);
        void y(float y);
        void z(float z);
    };

    struct SetPosition {
        void x(float x);
        void y(float y);
        void z(float z);
    };

    struct SetRotation {
        void x(float x);
        void y(float y);
        void z(float z);
    };
    // Methods to attach things through openGL, and if relevant, register it through OpenGL
    void Attach(ObjMesh *mesh);
    void Attach(IMaterial *material);
    void Attach(shader *shader);

    void useShader();
    
    unsigned int getVAO_ID();
    unsigned int getShaderID();
    unsigned int getVBO_ID();

    // Builds the buffer for this object and displays it
    void Instantiate();

    // Once object is deleted, destructor should handle the rest
    ~Object();
};

#endif