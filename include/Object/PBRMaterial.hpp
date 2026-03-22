#ifndef PBRMATERIAL_HPP
#define PBRMATERIAL_HPP

#include <memory>

#include "IMaterial.hpp"
#include "materialShader.hpp"

class PBRMaterial : IMaterial
{
private:
    // Note for later: Might make sense to replace this with a generalized
    // hash map/unordered_set in the IMaterial class

    // textureMaps[0] = pointer to diffuse textureData
    // textureMaps[1] = pointer to metallic textureData
    // textureMaps[2] = pointer to normals textureData
    // textureMaps[3] = pointer to roughness textureData
    vector<textureData *> textureMaps = vector<textureData *>(4);
    materialShader *matShader = nullptr;
public:
    void setDiffuse(textureData *diffuse);
    void setMetallic(textureData *metallic);
    void setNormals(textureData *normals);
    void setRoughness(textureData *roughness);

    void setShader(materialShader *shader);
    unsigned int getShader_ID();
    void useShader();


    void bindTextureMap(textureData *textureMap);
    void bindAllMaps();
};

#endif