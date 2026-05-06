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
public:
    virtual void loadMesh(string meshPath) = 0;

    void setVAO_ID(unsigned int ID) { VAO_ID = ID; }
    unsigned int getVAO_ID() { return VAO_ID; }

    void setEBO_ID(unsigned int ID) { EBO_ID = ID; }
    unsigned int getEBO_ID() { return EBO_ID; }
};

#endif