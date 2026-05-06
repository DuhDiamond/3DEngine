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
    static Camera* activeCamera;
    // This holds a vector of different loaded objects in the scene
    // The IndirectRender class will go through every object, and do the following:
    // - Add a new entry to the sceneMeshVBOBuffer and sceneMeshEBOBuffer if the mesh does not exist, alongside a pointer to cmd from the mesh
    // - Add a new entry to the
    vector<Object> sceneObjects = vector<Object>();

    vector<AmbientLight> ambientlights;
    vector<DirectionalLight> directionallights;
    vector<PointLight> pointlights;
};

#endif