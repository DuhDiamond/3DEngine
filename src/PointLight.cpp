#include "Lights/PointLight.hpp"
#include "Scene/Scene.hpp"

void PointLight::updateLightInCurrentShader() {
    unsigned int currShaderID;
    TexturedMonkeyShader.setVec3("pointlights[0].pos", pos);
    TexturedMonkeyShader.setVec3("pointlights[0].colour", colour);
}

TexturedMonkeyShader.setMat4("view", activeCamera->view);
TexturedMonkeyShader.setVec3("cameraViewPos", activeCamera->cameraPos);