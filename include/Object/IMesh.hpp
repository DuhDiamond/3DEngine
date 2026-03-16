#ifndef IMESH_HPP
#define IMESH_HPP

#include <glad/glad.h>
#include <string>
#include <vector>

using namespace std;

class IMesh
{
private:
    unsigned int VAO_ID;
    unsigned int EBO_ID;

    // This will hold this object's data in the format that OpenGL's pipeline expects in a dynamic array
    // To be passed in from the Object, which holds the VBO id
    float *objBuffer = nullptr;
    unsigned int bufferSize;
public:
    virtual void loadMesh(string meshPath) = 0;

    void setVAO_ID(unsigned int ID) { VAO_ID = ID; }
    unsigned int getVAO_ID() { return VAO_ID; }

    void setEBO_ID(unsigned int ID) { EBO_ID = ID; }
    unsigned int getEBO_ID() { return EBO_ID; }

    float *getBuffer() { return objBuffer; }
    void setBuffer(float *buffer) { objBuffer = buffer; }
    unsigned int getBufferSize() { return bufferSize; }
    void setBufferSize(unsigned int size) { bufferSize = size; }
};

#endif