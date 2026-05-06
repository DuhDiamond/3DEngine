#include "Scene/IndirectRender.hpp"

// Reads the object list, updates internal buffers and other vectors
void IndirectRender::readObjectList() {
    for (int i = 0; i < loadedObjects.size(); i++) {
        Object *currObject = loadedObjects[i];
        // if (loadedMeshes.find(currObject->objectMesh) == loadedMeshes.end()) {
        //     loadedMeshes.insert(currObject->objectMesh, 1);
        // }
    }
}

void IndirectRender::buildSceneBuffers() {
    unsigned int currentEBOByteOffset = 0;
    unsigned int currentBaseVertex = 0;

    for (int i = 0; i < loadedMeshes.size(); i++) {
        ObjMesh *currMesh = loadedMeshes[i];

        commands.push_back(currMesh->getCmd());
        // instanceInfo[0].push_back(currObject->);
        sceneVBOBuffer.insert(sceneVBOBuffer.end(), currMesh->VBOBuffer.begin(), currMesh->VBOBuffer.end());
        sceneEBOBuffer.insert(sceneEBOBuffer.end(), currMesh->EBOBuffer.begin(), currMesh->EBOBuffer.end());
        sceneEBOCounts.push_back(currMesh->EBOBuffer.size());
        sceneBaseVertexOffsets.push_back(currentBaseVertex);
        sceneBufferByteOffsets.push_back((void*)(uintptr_t)currentEBOByteOffset);

        currentEBOByteOffset += currMesh->EBOBuffer.size() * sizeof(unsigned int);
        currentBaseVertex    += currMesh->VBOBuffer.size() / 11;
    }

    glGenVertexArrays(1, &VAO_ID);
    glBindVertexArray(VAO_ID);

    glGenBuffers(1, &EBO_ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sceneEBOBuffer.size()*sizeof(unsigned int), sceneEBOBuffer.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &VBO_ID);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_ID);
    glBufferData(GL_ARRAY_BUFFER, sceneVBOBuffer.size()*sizeof(float), sceneVBOBuffer.data(), GL_STATIC_DRAW);
    
    // glGenBuffers();

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11*sizeof(float), (void*)0);
    
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11*sizeof(float), (void*)(3*sizeof(float)));
    
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11*sizeof(float), (void*)(6*sizeof(float)));
    
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11*sizeof(float), (void*)(8*sizeof(float)));

    glBindVertexArray(0);
}

void IndirectRender::drawAll() {
    glBindVertexArray(VAO_ID);

    glMultiDrawElementsBaseVertex(
        GL_TRIANGLES,
        (const GLsizei*)(sceneEBOCounts.data()),
        GL_UNSIGNED_INT,
        (const void**)(sceneBufferByteOffsets.data()),
        sceneEBOCounts.size(),
        sceneBaseVertexOffsets.data()
    );
}