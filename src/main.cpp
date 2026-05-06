#include <iostream>
#include <cmath>
#include <bits/stdc++.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stb/stb_image.h>

#include "Object/materialShader.hpp"
#include "Object/ObjMesh.hpp"
#include "Object/Object.hpp"
#include "Object/PBRMaterial.hpp"
#include "Scene/Clock.hpp"
#include "Scene/Camera.hpp"
#include "Scene/IndirectRender.hpp"

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main() {

    // various initializations and error checking
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    Camera::initializeViewport();

    GLFWwindow* window = glfwCreateWindow(Camera::getWidth(), Camera::getHeight(), "3DEngine", nullptr, nullptr);
    if (window == nullptr) {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }

    static Camera* activeCamera = nullptr;

    Camera Scene1Camera;
    Scene1Camera.initializeCamera();
    activeCamera = &Scene1Camera;

    auto active_camera_wrapper = [](GLFWwindow *window, double xPos, double yPos) {
        activeCamera->mouse_callback(window, xPos, yPos);
    };

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, active_camera_wrapper);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    glViewport(0, 0, Camera::getWidth(), Camera::getHeight());

    cout << "Initialized viewport" << endl;

    // Scene handling

    Camera sceneCamera;

    const char* vertexShader = "../shaders/vertexShader.glsl";
    const char* fragShader =   "../shaders/fragShader.glsl";
    
    // Mesh loading
    ObjMesh SuzanneMonkeyMesh;
    SuzanneMonkeyMesh.loadMesh("suzanneTriangulated2.obj");
    ObjMesh TeapotMesh;
    TeapotMesh.loadMesh("../Meshes/teapotTriangulatedUVMapped.obj");

    // Shader classses
    materialShader uber;
    uber.loadShader(vertexShader, fragShader);

    // Loaded texture classes
    textureData TexturedMonkeyDiffuse;
    TexturedMonkeyDiffuse.loadTexture("suzanneTexture.png", 0);


    PBRMaterial VertexColoursMonkeyMaterial;
    VertexColoursMonkeyMaterial.setShader(&uber);
    PBRMaterial TexturedMonkeyMaterial;
    TexturedMonkeyMaterial.setShader(&uber);
    TexturedMonkeyMaterial.setDiffuse(&TexturedMonkeyDiffuse);

    Object TexturedMonkey;
    TexturedMonkey.Attach(&SuzanneMonkeyMesh);
    TexturedMonkey.Attach(&TexturedMonkeyMaterial);

    Object VertexColoursMonkey;
    VertexColoursMonkey.Attach(&SuzanneMonkeyMesh);
    VertexColoursMonkey.Attach(&VertexColoursMonkeyMaterial);

    Object Teapot;
    Teapot.Attach(&TeapotMesh);
    Teapot.Attach(&VertexColoursMonkeyMaterial);

    TexturedMonkey.SetSize(1.0, 1.0, 1.0);
    TexturedMonkey.SetPosition(0.5, 0.2, -1.5);

    VertexColoursMonkey.SetSize(0.5, 0.5, 0.5);
    VertexColoursMonkey.SetPosition(-2.0, -1.0, -3.0);
    
    Teapot.SetSize(0.5, 1, 0.5);
    Teapot.SetPosition(0.0, 1.0, 0.5);

    glm::vec3 light1Pos = glm::vec3(-1.5, 0.0, 0.5);
    glm::vec3 light1Colour = glm::vec3(5.0, 5.0, 5.0);
    glm::vec3 light2Pos = glm::vec3(1.5, 0.0, 0.5);
    glm::vec3 light2Colour = glm::vec3(0.0, 5.0, 5.0);

    uber.useShader();
    unsigned int uberShaderID = uber.getShader_ID();
    uber.setMat4("projection", activeCamera->projection);
    uber.setVec3("pointlights[0].pos", light1Pos);
    uber.setVec3("pointlights[0].colour", light1Colour);
    uber.setVec3("pointlights[1].pos", light2Pos);
    uber.setVec3("pointlights[1].colour", light2Colour);

    IndirectRender renderer;

    renderer.loadedObjects.push_back(&TexturedMonkey);
    renderer.loadedObjects.push_back(&VertexColoursMonkey);
    renderer.loadedObjects.push_back(&Teapot);

    renderer.buildSceneBuffers();

    // Main render loop
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    while (!glfwWindowShouldClose(window)) {
        // Scene setup
        // timer.advanceTime();
        float currentTime = glfwGetTime();
        Camera::deltaTime = currentTime - Camera::previousTime;
        Camera::previousTime = currentTime;

        // input
        activeCamera->processInput(window);
        activeCamera->updateViewMatrix();

        // rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        uber.setMat4("view", activeCamera->view);
        uber.setVec3("cameraViewPos", activeCamera->cameraPos);
        
        TexturedMonkey.Draw();

        VertexColoursMonkey.Rotate(0.0, 0.5, 0.2*sin(currentTime));
        VertexColoursMonkey.Draw();

        Teapot.Translate(0.0, 0.0, 0.01*sin(currentTime));
        Teapot.Draw();

        renderer.drawAll();

        // events and buffer swap
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();

    return 0;
}