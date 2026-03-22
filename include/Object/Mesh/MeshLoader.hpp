#ifndef MESHLOADER_HPP
#define MESHLOADER_HPP

#include "Mesh.hpp"

// Abstract factory for various mesh data structure types
class MeshLoader {
private:
public:
    virtual Mesh loadMesh(const char* meshPath) = 0;
};

class ObjLoader : MeshLoader {
private:
    vector<float[4]> readVertexData(const char* ObjPath);
    vector<float[3]> readVertexNormalsData(const char* ObjPath);
    vector<float[3]> readVertexTextureCoordsData(const char* ObjPath);
    vector<float[3]> readVertexNormalsData(const char* ObjPath);
public:
    Mesh loadMesh(const char* meshPath);
};

#endif