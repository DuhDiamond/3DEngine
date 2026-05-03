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
#include "triangle.cpp"

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main() {

    // various initializations and error checking
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    Camera::initializeViewport();

    GLFWwindow* window = glfwCreateWindow(Camera::getWidth(), Camera::getHeight(), "3DEngine", nullptr, nullptr);
    if (window == nullptr) {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }

    static Camera* active_camera = nullptr;

    Camera Scene1Camera;
    Scene1Camera.initializeCamera();
    active_camera = &Scene1Camera;

    // std::function<void(GLFWwindow*, double, double)> activeCamera = [&](GLFWwindow* window, double xpos, double ypos){ return Scene1Camera.mouse_callback(window, xpos, ypos); };
    // auto activeCamera = [&](function<void(GLFWwindow*, double, double)>) { Camera::*Scene1Camera.mouse_callback; }
    // void (Camera::*activeCamera)(GLFWwindow*, double, double) = Camera::mouse_callback_camerawrapper(Scene1Camera);

    auto active_camera_wrapper = [](GLFWwindow *window, double xPos, double yPos) {
        active_camera->mouse_callback(window, xPos, yPos);
    };

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, active_camera_wrapper);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    // GLFW's OpenGL viewport configuration
    glViewport(0, 0, Camera::getWidth(), Camera::getHeight());

    cout << "Initialized viewport" << endl;

    Camera sceneCamera;

    // Will need to abstract away and clean up this logic later; currently set up for testing
    // To call "Instantiate", you will need at minimum a ObjMesh attached,
    // but a shader is also necessary for it to render
    
    // Loading the mesh for both Monkey objects ("Suzanne" is the name of the Blender monkey face)
    ObjMesh SuzanneMonkeyMesh;
    SuzanneMonkeyMesh.loadMesh("suzanneTriangulated2.obj");

    // Textured Monkey model setup

    const char* PhongVertexShader = "../shaders/PhongVertexShader.glsl";
    const char* DiffuseTexturePhongFragmentShader =   "../shaders/DiffuseTexturePhongFragmentShader.glsl";
    materialShader TexturedMonkeyShader;
    TexturedMonkeyShader.loadShader(PhongVertexShader, DiffuseTexturePhongFragmentShader);


    textureData TexturedMonkeyDiffuse;
    TexturedMonkeyDiffuse.loadTexture("suzanneTexture.png");

    PBRMaterial TexturedMonkeyMaterial;
    TexturedMonkeyMaterial.setDiffuse(&TexturedMonkeyDiffuse);
    TexturedMonkeyMaterial.setShader(&TexturedMonkeyShader);

    Object TexturedMonkey;
    TexturedMonkey.Attach(&SuzanneMonkeyMesh);
    TexturedMonkey.Attach(&TexturedMonkeyMaterial);

    // Instantiate at the moment just sets the internal buffer pointer and runs recomputeModelMatrix()
    TexturedMonkey.SetSize(1.0, 1.0, 1.0);
    TexturedMonkey.SetPosition(0.5, 0.2, -1.5);
    // TexturedMonkey.Instantiate();

    // Vertex Colours Monkey model setup (the one with the painted-on colours)
    const char* VertexColoursPhongFragmentShader =   "../shaders/vertexColoursPhongFragmentShader.glsl";
    materialShader VertexColoursMonkeyShader;

    // For future: Set up seperate fragment and vertex shader classes that the materialShader class
    // has pointers to, like the Object class in relation to ObjMesh and PBRMaterial (minimizes repetitive loading)
    VertexColoursMonkeyShader.loadShader(PhongVertexShader, VertexColoursPhongFragmentShader);

    PBRMaterial VertexColoursMonkeyMaterial;
    VertexColoursMonkeyMaterial.setShader(&VertexColoursMonkeyShader);

    Object VertexColoursMonkey;
    // Example of why i'm using pointers; can reuse already loaded meshes with their VBOs,
    // just change the uniforms for the model matrix data
    // Note for future: look into how to utilize glMultiDrawElements() or the newer methods for instanced
    // meshes, may be more efficient
    VertexColoursMonkey.Attach(&SuzanneMonkeyMesh);
    VertexColoursMonkey.Attach(&VertexColoursMonkeyMaterial);

    VertexColoursMonkey.SetSize(0.5, 0.5, 0.5);
    VertexColoursMonkey.SetPosition(-2.0, -1.0, -3.0);
    // VertexColoursMonkey.Instantiate();

    // The Teapot Object

    // Note: I don't actually use the UV map on this object at the moment
    ObjMesh TeapotMesh;
    TeapotMesh.loadMesh("../Meshes/teapotTriangulatedUVMapped.obj");

    materialShader TeapotShader;
    TeapotShader.loadShader(PhongVertexShader, VertexColoursPhongFragmentShader);
    
    Object Teapot;
    Teapot.Attach(&TeapotMesh);
    // // Showing how Materials can also be reused;
    // // this will just draw the Teapot's vertex colours instead, however, since the Teapot .obj has no colours,
    // // the buffer loads to the fallback (0.5, 0.5, 0.5) grey colour for every corresponding vertex
    // // Thus, the object will render a default grey colour
    Teapot.Attach(&VertexColoursMonkeyMaterial);

    Teapot.SetSize(0.5, 1, 0.5);
    Teapot.SetPosition(0.0, 1.0, 0.5);
    // Teapot.Instantiate();

    TexturedMonkey.useShader();
    unsigned int TexturedMonkey_Shader_ID = TexturedMonkey.getShader_ID();
    glUniformMatrix4fv(glGetUniformLocation(TexturedMonkey_Shader_ID, "projection"), 1, GL_FALSE, glm::value_ptr(active_camera->projection));
    
    VertexColoursMonkey.useShader();
    unsigned int VertexColoursMonkey_Shader_ID = VertexColoursMonkey.getShader_ID();    
    glUniformMatrix4fv(glGetUniformLocation(VertexColoursMonkey_Shader_ID, "projection"), 1, GL_FALSE, glm::value_ptr(active_camera->projection));


    unsigned int Teapot_Shader_ID = Teapot.getShader_ID();
    Teapot.useShader();
    glUniformMatrix4fv(glGetUniformLocation(Teapot_Shader_ID, "projection"), 1, GL_FALSE, glm::value_ptr(active_camera->projection));

    // Main render loop
    glEnable(GL_DEPTH_TEST);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // glPointSize(5);
    // glLineWidth(5);

    glEnable(GL_CULL_FACE);

    glm::vec3 light1Pos = glm::vec3(-1.5, 0.0, 0.5);
    glm::vec3 light1Colour = glm::vec3(5.0, 5.0, 5.0);
    glm::vec3 light2Pos = glm::vec3(1.5, 0.0, 0.5);
    glm::vec3 light2Colour = glm::vec3(0.0, 5.0, 5.0);

    while (!glfwWindowShouldClose(window)) {
        // Scene setup
        // timer.advanceTime();
        float currentTime = glfwGetTime();
        Camera::deltaTime = currentTime - Camera::previousTime;
        Camera::previousTime = currentTime;

        // input
        active_camera->processInput(window);
        active_camera->updateViewMatrix();

        // rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Manually testing the view matrices here (will be implemented in Camera class)
        TexturedMonkey.useShader();
        TexturedMonkeyShader.setMat4("view", active_camera->view);
        TexturedMonkeyShader.setVec3("cameraViewPos", active_camera->cameraPos);
        TexturedMonkeyShader.setVec3("pointlights[0].pos", light1Pos);
        TexturedMonkeyShader.setVec3("pointlights[0].colour", light1Colour);
        TexturedMonkeyShader.setVec3("pointlights[1].pos", light2Pos);
        TexturedMonkeyShader.setVec3("pointlights[1].colour", light2Colour);
        
        VertexColoursMonkey.useShader();
        VertexColoursMonkeyShader.setMat4("view", active_camera->view);
        VertexColoursMonkeyShader.setVec3("cameraViewPos", active_camera->cameraPos);
        VertexColoursMonkeyShader.setVec3("pointlights[0].pos", light1Pos);
        VertexColoursMonkeyShader.setVec3("pointlights[0].colour", light1Colour);
        VertexColoursMonkeyShader.setVec3("pointlights[1].pos", light2Pos);
        VertexColoursMonkeyShader.setVec3("pointlights[1].colour", light2Colour);

        Teapot.useShader();
        TeapotShader.setMat4("view", active_camera->view);
        TeapotShader.setVec3("cameraViewPos", active_camera->cameraPos);
        TeapotShader.setVec3("pointlights[0].pos", light1Pos);
        TeapotShader.setVec3("pointlights[0].colour", light1Colour);
        TeapotShader.setVec3("pointlights[1].pos", light2Pos);
        TeapotShader.setVec3("pointlights[1].colour", light2Colour);

        // Note for later: Standardize it with the timer class to properly make use of deltaTime
        // TexturedMonkey.Rotate(0.0, 0.0, 0.0);
        TexturedMonkey.Draw();

        // VertexColoursMonkey.SetPosition(0, cos((float)glfwGetTime()), -3);
        VertexColoursMonkey.Rotate(0.0, 0.5, 0.2*sin(currentTime));
        VertexColoursMonkey.Draw();

        Teapot.Translate(0.0, 0.0, 0.01*sin(currentTime));
        Teapot.Draw();

        // events and buffer swap
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    /*
    glDeleteVertexArrays(1, &VAO1);
    glDeleteVertexArrays(1, &VAO2);

    glDeleteBuffers(1, &VBO1);
    glDeleteBuffers(1, &VBO2);

    glDeleteBuffers(1, &EBO1);
    glDeleteBuffers(1, &EBO2);
    */

    glfwTerminate();

    return 0;
}