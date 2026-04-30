#include <memory>

#include "Object/PBRMaterial.hpp"

using namespace std;

void PBRMaterial::setDiffuse(textureData *diffuse) { textureMaps[0] = diffuse; }
void PBRMaterial::setMetallic(textureData *metallic) { textureMaps[1] = metallic; }
void PBRMaterial::setNormals(textureData *normals) { textureMaps[2] = normals; }
void PBRMaterial::setRoughness(textureData *roughness) { textureMaps[3] = roughness; }

void PBRMaterial::bindTextureMap(textureData *textureMap)
{
    textureMap->bindTexture();
}

void PBRMaterial::bindAllMaps()
{
    for (textureData *textureMap : textureMaps) {
        if (textureMap != nullptr) textureMap->bindTexture();
    }
}

void PBRMaterial::setShader(materialShader *shader) { matShader = shader; }
unsigned int PBRMaterial::getShader_ID() { return matShader->getShader_ID(); }
void PBRMaterial::useShader() { matShader->useShader(); }
void PBRMaterial::updateModelMatrix(glm::mat4 storedModelMatrix) { matShader->setMat4("model", storedModelMatrix); }