#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

#include "fileLoaders/MeshLoader.hpp"
#include "Object/ObjMesh.hpp"

using namespace std;

void ObjMesh::readVertexCoordinateData(stringstream &linestream)
{
    // cout << "Creating new position coordinate number " << positionCount + 1 << endl;
    // Initialize new vertex in the vertexBuffer list
    position pos;
    linestream >> pos.x >> pos.y >> pos.z;
    // cout << pos.x << " " << pos.y << " " << pos.z << endl;
    // If vertex colours exist, add them immediately (information is on same line as position)
    if (!linestream.eof()) {
        // cout << "Creating new vertex colour number " << colCount + 1 << endl;
        colour col;
        linestream >> col.r;
        linestream >> col.g;
        linestream >> col.b;
        // cout << pos.r << " " << pos.g << " " << pos.b << endl;
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
        EBOIndices.push_back(stoi(positionCoordinateIndex) - 1);
        // Empty checks are to make sure that associated data was actually in the file (otherwise the vectors are empty)
                                         v.positionCoordinate = &positionCoordinates[stoi(positionCoordinateIndex) - 1];
        if (!vertexColours.empty())      v.vertexColour =       &vertexColours[stoi(positionCoordinateIndex) - 1];
        if (!textureCoordinates.empty()) v.textureCoordinate =  &textureCoordinates[stoi(textureCoordinateIndex) - 1];
        if (!normalCoordinates.empty())  v.normalCoordinate =   &normalCoordinates[stoi(normalCoordinateIndex) - 1];

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
    string absolutePath = "../" + meshPath;
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
        } catch (exception e) {
            cout << "ERROR: mesh file not successfully read:" << endl;
            if (objFile.badbit)  perror("objFile: badbit (read/write error on i/o)");
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
    return EBOIndices.size();
}

void ObjMesh::buildBuffer() {

    cout << "Starting build process: " << endl;

    unsigned int VAO_ID;
    glGenVertexArrays(1, &VAO_ID);
    glBindVertexArray(VAO_ID);
    setVAO_ID(VAO_ID);

    unsigned int *EBOBuffer = new unsigned int[EBOIndices.size()];

    for (int i = 0; i < EBOIndices.size(); i++) {
        EBOBuffer[i] = EBOIndices[i];
    }

    unsigned int EBO_ID;

    glGenBuffers(1, &EBO_ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, EBOIndices.size()*sizeof(unsigned int), EBOBuffer, GL_STATIC_DRAW);
    glBindVertexArray(0);

    delete[] EBOBuffer;
    setEBO_ID(EBO_ID);

    glBindVertexArray(getVAO_ID());

    int bufferSize = 0;
    for (polygon &face : polygonList) {
        // 11 elements per vertex in the vector per face
        bufferSize += face.polygonVertices.size() * 11;
        for (vertex &v : face.polygonVertices) {
            unorderedVertices.push_back(v);
        }
    }

    // Note for later: organize logic around smart pointers
    // (and make sure memory management gets handled properly)
    float *buffer = getBuffer();
    buffer = new float[bufferSize];

    setBuffer(buffer);
    setBufferSize(bufferSize);


    // Note for later: reorganize this into a seperate function
    for (int j = 0; j < EBOIndices.size(); j++) {
        unsigned int bufferIndex = EBOIndices[j] * 11;
        vertex &v = unorderedVertices[j];
        buffer[bufferIndex] = v.positionCoordinate->x;
        buffer[bufferIndex + 1] = v.positionCoordinate->y;
        buffer[bufferIndex + 2] = v.positionCoordinate->z;
        if (!vertexColours.empty()) buffer[bufferIndex + 3] = v.vertexColour->r;
        if (!vertexColours.empty()) buffer[bufferIndex + 4] = v.vertexColour->g;
        if (!vertexColours.empty()) buffer[bufferIndex + 5] = v.vertexColour->b;
        if (!textureCoordinates.empty()) buffer[bufferIndex + 6] = v.textureCoordinate->u;
        if (!textureCoordinates.empty()) buffer[bufferIndex + 7] = v.textureCoordinate->v;
        if (!normalCoordinates.empty()) buffer[bufferIndex + 8] = v.normalCoordinate->x;
        if (!normalCoordinates.empty()) buffer[bufferIndex + 9] = v.normalCoordinate->y;
        if (!normalCoordinates.empty()) buffer[bufferIndex + 10] = v.normalCoordinate->z;
    }

    cout << "Build process done!" << endl;
}