#ifndef OBJMESH_HPP
#define OBJMESH_HPP

#include "IMesh.hpp"

// This will hold the raw object data after it's read in from an OBJ file, returned by ObjLoader
class ObjMesh : public IMesh
{
private:
    // Pointer which holds the associated ID for the loaded mesh's buffered data
    unsigned int VBO_ID;

    // List of geometric coordinates
    struct position
    {
        float x;
        float y;
        float z;
    };
    vector<position> positionCoordinates;

    // Vertex colours, as sometimes exported in some obj exporters like
    // Blender and 3DSMax. This won't be in every OBJ file
    // Note: Blender does not export these as 6-decimal floats, but 4-decimal numbers
    // May need to be changed (if it can't represent same type of numbers)

    struct colour {
        float r;
        float g;
        float b;
    };
    vector<colour> vertexColours;

    // List of vertex normals (x, y, z)
    // Note: Blender does not export these as 6-decimal floats, but 4-decimal numbers
    // May need to be changed (if it can't represent same type of numbers)
    struct normal
    {
        float x;
        float y;
        float z;
    };
    vector<normal> normalCoordinates;

    struct uv
    {
        float u;
        float v;
    };
    vector<uv> textureCoordinates;

    struct vertex
    {
        position *positionCoordinate = nullptr;
        colour *vertexColour = nullptr;
        uv *textureCoordinate = nullptr;
        normal *normalCoordinate = nullptr;
    };
    vector<vertex> unorderedVertices;
    
    // Holds the face data from the OBJ file format (denoted by "f" on each line)
    struct polygon
    {
        vector<vertex> polygonVertices;
    };
    vector<polygon> polygonList;

    vector<unsigned int> EBOIndices;

    // readVertexCoordinateData handles both vertex position and vertex colours
    void readVertexCoordinateData(stringstream &linestream);
    void readVertexNormalData(stringstream &linestream);
    void readVertexTextureCoordinateData(stringstream &linestream);
    void readPolygonFaceIndices(string &element, stringstream &linestream, stringstream &vertexstream);
    
    void buildBuffer();

public:
    void loadMesh(string meshPath);

    void bindMeshVAO();
    unsigned int getEBOSize();
    unsigned int getVBO_ID();
};

#endif