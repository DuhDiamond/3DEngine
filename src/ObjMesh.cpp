#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "fileLoaders/MeshLoader.hpp"
#include "Object/ObjMesh.hpp"

using namespace std;

void ObjMesh::readVertexCoordinateData(stringstream &linestream)
{
    // cout << "Creating new position coordinate number " << positionCount + 1 << endl;
    // Initialize new vertex in the vertexBuffer list
    position pos;
    linestream >> pos.x;
    linestream >> pos.y;
    linestream >> pos.z;
    // cout << pos.x << " " << pos.y << " " << pos.z << endl;
    // If vertex colours exist, add them immediately (information is on same line as position)
    if (!linestream.eof()) {
        // cout << "Creating new vertex colour number " << colCount + 1 << endl;
        colour col;
        linestream >> col.r;
        linestream >> col.g;
        linestream >> col.b;
        // cout << col.r << " " << col.g << " " << col.b << endl;
        vertexColours.push_back(col);
    }
    positionCoordinates.push_back(pos);
}

void ObjMesh::readVertexNormalData(stringstream &linestream)
{
    // cout << "Creating new normal coordinate number " << normalCount + 1 << endl;
    normal n;
    linestream >> n.x;
    linestream >> n.y;
    linestream >> n.z;
    // cout << n.x << " " << n.y << " " << n.z << endl;
    normalCoordinates.push_back(n);
}

void ObjMesh::readVertexTextureCoordinateData(stringstream &linestream)
{
    // cout << "Creating new texture coordinate number " << textureCoordinateCount + 1 << endl;
    uv texCoord;
    linestream >> texCoord.u;
    linestream >> texCoord.v;
    // cout << "texCoord: " << endl;
    // cout << texCoord.u << " " << texCoord.v << endl;
    textureCoordinates.push_back(texCoord);
}

void ObjMesh::readPolygonFaceIndices(string &element, stringstream &linestream, stringstream &vertexstream)
{
    // cout << "Creating new polygon number " << polygonCount + 1 << endl;
    polygon face;
    while (!linestream.eof()) {
        // Parse through each polygon
        linestream >> element;
        vertexstream.clear();
        vertexstream.str(element);

        // For each polygon, get the corresponding index for each element
        // (Needs to be string to match expected getline parameters)
        string positionCoordinateIndex;
        string textureCoordinateIndex;
        string normalCoordinateIndex;
        getline(vertexstream, positionCoordinateIndex, '/');
        getline(vertexstream, textureCoordinateIndex, '/');
        getline(vertexstream, normalCoordinateIndex, '/');

        vertex v;
        // cout << posCoordIndex << endl;
        // cout << normalCoordIndex << endl;
        // cout << texCoordIndex << endl;

        // -1 since the obj format isn't 0-indexed like arrays/vectors
        // Empty checks are to make sure that associated data was actually in the file (otherwise the vectors are empty)
                                         v.positionCoordinateIndex = stoi(positionCoordinateIndex) - 1;
        if (!vertexColours.empty())      v.vertexColourIndex =       stoi(positionCoordinateIndex) - 1;
        if (!textureCoordinates.empty()) v.textureCoordinateIndex =  stoi(textureCoordinateIndex) - 1;
        if (!normalCoordinates.empty())  v.normalCoordinateIndex =   stoi(normalCoordinateIndex) - 1;

        // cout << "Vertex for polygon complete" << endl;
        face.polygonVertices.push_back(v);
    }
    // Faces no longer use the same format as vertices,
    // so need to iterate through rest manually
    polygonList.push_back(face);
    linestream.clear();
}

void ObjMesh::loadMesh(string meshPath)
{
    // Since filepaths are relative to where executable is run, and it builds into the build folder,
    // I need to do this for now; will figure out a more proper way to manage it later
    string absolutePath = "../Meshes/" + meshPath;
    ifstream objFile;

    cout << absolutePath << endl;

    objFile.open(absolutePath);
    objFile.exceptions(ifstream::badbit);

    if (objFile.is_open()) {
        try {
            string line, element;
            stringstream linestream, vertexstream;

            while(getline(objFile, line)) {
                linestream.clear();
                linestream.str(line);
                linestream >> element;
                // cout << "Copying in element: " << element << endl;

                if (element == "v")
                {
                    readVertexCoordinateData(linestream);
                }
                else if (element == "vn")
                {
                    readVertexNormalData(linestream);
                }
                else if (element == "vt")
                {
                    readVertexTextureCoordinateData(linestream);
                }
                else if (element == "f")
                {
                    readPolygonFaceIndices(element, linestream, vertexstream);
                }
                else {
                    cout << "Unimplemented element type in file: " << element << endl;
                }
            }
            objFile.close();

            cout << "SUCCESS: copied in mesh from " << meshPath << " with:" << endl;
            cout << "---------------------------------------" << endl;
            cout << positionCoordinates.size() << " vertices" << endl;
            cout << normalCoordinates.size() << " vertexNormals" << endl;
            cout << textureCoordinates.size() << " textureCoordinates" << endl;
            cout << polygonList.size() << " faces" << endl;
            cout << "---------------------------------------" << endl;

            buildBuffer();

        } catch (exception e) {
            cout << "ERROR: mesh file not successfully read:" << endl;
            if (objFile.badbit) perror("objFile: badbit (read/write error on i/o)");
            // if (objFile.failbit) perror("objFile: failbit (logic error on i/o)");
            
            cout << "Information: " << e.what() << endl;
        }
    } else {
        cout << "Error: Mesh (obj) file not successfully opened:" << endl;
        if (!objFile) {
            perror("open failure for obj file");
        }
        cout << meshPath << endl;
    }
}

unsigned int ObjMesh::getEBOSize() {
    return EBOBuffer.size();
}

void ObjMesh::buildBuffer() {
    cout << "Starting build process: " << endl;


    // Deduplication of duplicate vertices while building the EBO indirectly
    for (polygon &face : polygonList) {
        for (vertex &v : face.polygonVertices) {
            vector<unsigned int> key;
            key.push_back(v.positionCoordinateIndex);
            key.push_back(v.vertexColourIndex);
            key.push_back(v.textureCoordinateIndex);
            key.push_back(v.normalCoordinateIndex);

            if (deduplicatedVertexMap.find(key) == deduplicatedVertexMap.end()) {
                deduplicatedVertexMap[key] = deduplicatedVertices.size();
                deduplicatedVertices.push_back(v);
            }
            EBOBuffer.push_back(deduplicatedVertexMap[key]);
        }
    }

    VBOBuffer.resize(deduplicatedVertices.size() * 11);
    // Note for later: reorganize this into a seperate function
    for (int i = 0; i < deduplicatedVertices.size(); i++) {
        vertex &v = deduplicatedVertices[i];
        int j = i * 11;
                                         VBOBuffer[j]     = positionCoordinates[v.positionCoordinateIndex].x;
                                         VBOBuffer[j + 1] = positionCoordinates[v.positionCoordinateIndex].y;
                                         VBOBuffer[j + 2] = positionCoordinates[v.positionCoordinateIndex].z;
        // If the file does not have vertex colours, should default to (0.5, 0.5, 0.5) (grey)
        if (!vertexColours.empty())      VBOBuffer[j + 3] = vertexColours[v.vertexColourIndex].r; else VBOBuffer[j + 3] = 0.5;
        if (!vertexColours.empty())      VBOBuffer[j + 4] = vertexColours[v.vertexColourIndex].g; else VBOBuffer[j + 4] = 0.5;
        if (!vertexColours.empty())      VBOBuffer[j + 5] = vertexColours[v.vertexColourIndex].b; else VBOBuffer[j + 5] = 0.5;
        if (!textureCoordinates.empty()) VBOBuffer[j + 6] = textureCoordinates[v.textureCoordinateIndex].u;
        // Note for later: Temporary swap to fix texture coordinates, as apparently my currently
        // loaded texture uses the directX convention (need to instead read in 1-v)
        // Should probably handle this according to a parameter input for the function
        if (!textureCoordinates.empty()) VBOBuffer[j + 7] = 1.0 - textureCoordinates[v.textureCoordinateIndex].v;
        if (!normalCoordinates.empty())  VBOBuffer[j + 8] = normalCoordinates[v.normalCoordinateIndex].x;
        if (!normalCoordinates.empty())  VBOBuffer[j + 9] = normalCoordinates[v.normalCoordinateIndex].y;
        if (!normalCoordinates.empty())  VBOBuffer[j + 10]= normalCoordinates[v.normalCoordinateIndex].z;
    }

    unsigned int VAO_ID;
    glGenVertexArrays(1, &VAO_ID);
    glBindVertexArray(VAO_ID);

    unsigned int EBO_ID;
    glGenBuffers(1, &EBO_ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, EBOBuffer.size()*sizeof(unsigned int), EBOBuffer.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &VBO_ID);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_ID);
    glBufferData(GL_ARRAY_BUFFER, VBOBuffer.size()*sizeof(float), VBOBuffer.data(), GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11*sizeof(float), (void*)0);
    
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11*sizeof(float), (void*)(3*sizeof(float)));
    
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11*sizeof(float), (void*)(6*sizeof(float)));
    
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11*sizeof(float), (void*)(8*sizeof(float)));

    glBindVertexArray(0);

    setVAO_ID(VAO_ID);
    setEBO_ID(EBO_ID);
    
    cmd.count = EBOBuffer.size();
    cmd.instanceCount = 0;
    cmd.firstIndex = 0;
    cmd.baseVertex = 0;
    cmd.baseInstance = 0;

    cout << "Build process done!" << endl;
}

void ObjMesh::bindMeshVAO() { glBindVertexArray(getVAO_ID()); }

unsigned int ObjMesh::getVBO_ID() { return VBO_ID; }