#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Object.hpp"
#include "Camera.hpp"
#include "Lights/AmbientLight.hpp"
#include "Lights/DirectionalLight.hpp"
#include "Lights/PointLight.hpp"

using namespace std;

// Singleton class to represent all the instanced scene data
class Scene {
public:

    vector<materialShader> loadedShaders = vector<materialShader>();

    // This holds a vector of different loaded objects in the scene
    vector<Object> sceneObjects = vector<Object>();

    static Camera* activeCamera;

    vector<AmbientLight> ambientlights;
    vector<DirectionalLight> directionallights;
    vector<PointLight> pointlights;

    // contains a vector<pointlight>, vector<directionallight>, vector<ambientlight> etc...

    // ...
    // Other future scene data will go here
    // ...

    //

    void render();

    // In case of direct (non-batched) rendering:

    // For shader in scene:
        // Bind VAO
        // For each material linked to shader:
            // Bind each texture (sampler2D)
            // Bind each VBO (auto-binds EBO)
                // Draw each mesh instance

    // In case of indirect (and batched) rendering:
    // To be determined
};

#endif