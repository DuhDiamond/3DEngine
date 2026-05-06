#include <vector>

#include "Object/ObjMesh.hpp"
#include "Object/Object.hpp"

class IndirectRender {
private:
    vector<int> sceneEBOCounts;
    vector<int> sceneBaseVertexOffsets;
    vector<void*> sceneBufferByteOffsets;

    vector<DrawElementsIndirectCommand*> commands;
    // a vector of vectors, each inner vector representing a loaded mesh in the scene
    vector<vector<perInstanceObjectBuffer*>> instanceInfo;

    unsigned int VAO_ID;
    unsigned int VBO_ID;
    unsigned int EBO_ID;

    // Used for per-instance parameters (model matrix, etc.)
    unsigned int IndirectBuffer_ID;

    vector<float> sceneVBOBuffer;
    vector<unsigned int> sceneEBOBuffer;

    vector<ObjMesh*> loadedMeshes = vector<ObjMesh*>();
    vector<PBRMaterial*> loadedMaterials = vector<PBRMaterial*>();
public:
    vector<Object*> loadedObjects = vector<Object*>();

    void readObjectList();
    void buildSceneBuffers();

    void drawAll();
};