#ifndef SCENE_H
#define SCENE_H

#include <glad/glad.h>
#include <vector>

#include "Object.hpp"

using namespace std;

// Singleton class to represent all the instanced scene data
class Scene {
public:
    // This holds a vector of different loaded objects in the scene
    vector<Object> sceneObjects = vector<Object>();

    // ...
    // Other future scene data will go here
    // ...

    // This method should go through and call DrawAll() on every Object in the scene,
    // which will call Draw() on every ObjectInstance in instances belonging to that object
    void render();
};

#endif