#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <vector>

#include "textureData.hpp"
#include "shader.hpp"


class Material {
private:
    // Will hold relevant texture data sets according to the material type that inherits it
    shader *materialShader = nullptr;
public:
};

class PBRMaterial : Material {
private:
    textureData *diffuse = nullptr;
    textureData *metallic = nullptr;
    textureData *normals = nullptr;
    textureData *roughness = nullptr;
public:
    PBRMaterial();
    void loadDiffuse(const textureData *texture);
    void loadMetallic(const textureData *texture);
    void loadNormals(const textureData *texture);
    void loadRoughness(const textureData *texture);
    ~PBRMaterial();
};

#endif