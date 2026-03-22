#include <vector>
#include <string>

#include "fileLoaders/MeshLoader.hpp"
#include "Object/ObjMesh.hpp"

using namespace std;

// To be repurposed later for general scene object/mesh management
// At the moment my pure pointers/loading approach is easier per-object,
// but this could still be useful for handling VAO binding efficiently

/*
IMesh *ObjLoader::createMesh(string meshPath)
{
    IMesh *newObjMesh = new ObjMesh();
    newObjMesh->loadMesh(meshPath);
    return newObjMesh;
}
*/