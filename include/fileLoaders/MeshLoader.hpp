#ifndef MESHLOADER_HPP
#define MESHLOADER_HPP

#include <string>

#include "Object/IMesh.hpp"

using namespace std;

// Abstract factory for various mesh data structure types
class MeshLoader
{
private:
public:
    virtual IMesh *createMesh(string meshPath) = 0;
};

class ObjLoader : MeshLoader
{
private:
public:
    IMesh *createMesh(string meshPath) override;
};

#endif