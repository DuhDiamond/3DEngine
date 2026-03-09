#ifndef MESH_HPP
#define MESH_HPP

#include <glad/glad.h>
#include <vector>

using namespace std;

class Mesh {
private:
    unsigned int *VAO_ID = nullptr;
    unsigned int *EBO_ID = nullptr;
public:
};

// This will hold the raw object data after it's read in from an OBJ file, returned by ObjLoader
class ObjMesh : Mesh {
private:
public:
    // List of geometric coordinates (x, y, z, w) (w optional, defaults to 1.0)
    vector<float[4]> vertexCoordinates;
    // List of vertex texture coordinates (u, [v, w])
    vector<float[3]> vertexTextureCoordinates;
    // List of vertex normals (x, y, z)
    vector<float[3]> vertexNormalCoordinates;
    // List of parameter space vertices (u, [v, w]) (not sure if I will need this yet)
    vector<float[3]> vertexParameterCoordinates;

    // Holds the face data from the OBJ file format (denoted by "f" on each line)
    struct face {
        // vertex indices (x, y, z) per face; mandatory: can degenerate it into the EBO format
        vector<unsigned int> vertexIndices;
        // vertex texture coordinate indices per face; can be empty
        vector<unsigned int> vertexTextureIndices;
        // vertex normal indices indices per face; can be empty
        vector<unsigned int> vertexNormalIndices;
    };
    vector<face> polygons;

    // Line element data (not sure if I will use this yet); initialized only once with initialize(), also denoted by "l" in an obj file
    struct line {
        vector<unsigned int> lineIndices;
    };
    vector<line> lines;
};

#endif