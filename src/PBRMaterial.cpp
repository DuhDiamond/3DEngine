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
    for (int i = 0; i < textureMaps.size(); i++) {
        if (textureMaps[i] != nullptr) {
            textureMaps[i]->bindTexture();
        } else {
            // Clear from previous object
            textureMaps[i]->clearTexture();
        }
    }
}

void PBRMaterial::setShader(materialShader *shader) { matShader = shader; }
unsigned int PBRMaterial::getShader_ID() { return matShader->getShader_ID(); }
void PBRMaterial::useShader() { matShader->useShader(); }
void PBRMaterial::updateModelMatrix(glm::mat4 storedModelMatrix) { matShader->setMat4("model", storedModelMatrix); }