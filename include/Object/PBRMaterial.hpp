#ifndef PBRMATERIAL_HPP
#define PBRMATERIAL_HPP

#include "IMaterial.hpp"

class PBRMaterial : IMaterial
{
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