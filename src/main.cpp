#include <iostream>
#include <cmath>

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
#include "triangle.cpp"

using namespace std;

const unsigned int SCREEN_WIDTH = 1920;
const unsigned int SCREEN_HEIGHT = 1080;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

float deltaTime = 0.0;
float previousTime = 0.0;

glm::vec3 cameraPos = glm::vec3(0.0, 0.0, 3.0);
glm::vec3 cameraFront = glm::vec3(0.0, 0.0, -1.0);
glm::vec3 cameraUp = glm::vec3(0.0, 1.0, 0.0);

float yaw = -90.0;
float pitch = 0.0;

const float cameraSpeed = 2.0;
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        cameraPos += cameraFront * cameraSpeed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        cameraPos -= cameraFront * cameraSpeed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        cameraPos += cameraUp * cameraSpeed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        cameraPos -= cameraUp * cameraSpeed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        yaw -= 0.1;
        glm::vec3 cameraDirection = glm::vec3(
            cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
            sin(glm::radians(pitch)),
            sin(glm::radians(yaw)) * cos(glm::radians(pitch))
        );
        cameraFront = glm::normalize(cameraDirection);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        yaw += 0.1;
        glm::vec3 cameraDirection = glm::vec3(
            cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
            sin(glm::radians(pitch)),
            sin(glm::radians(yaw)) * cos(glm::radians(pitch))
        );
        cameraFront = glm::normalize(cameraDirection);
    }
}

// Program starts at center of the screen
float previous_xPos = (float)SCREEN_WIDTH/2.0, previous_yPos = (float)SCREEN_HEIGHT/2.0;
const float sensitivity = 0.001;

bool firstMouse = false;

void mouse_callback(GLFWwindow* window, double xPos, double yPos) {
    if (firstMouse) {
        previous_xPos = xPos;
        previous_yPos = yPos;
        firstMouse = true;
    }

    float deltaX = xPos - previous_xPos;
    float deltaY = yPos - previous_yPos;
    previous_xPos = xPos;
    previous_yPos = yPos;

    deltaX *= sensitivity;
    deltaY *= sensitivity;

    yaw += deltaX;
    pitch -= deltaY;
    if (pitch > 89.0) pitch = 89.0;
    if (pitch < -89.0) pitch = -89.0;

    glm::vec3 cameraDirection = glm::vec3(
        cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
        sin(glm::radians(pitch)),
        sin(glm::radians(yaw)) * cos(glm::radians(pitch))
    );
    cameraFront = glm::normalize(cameraDirection);
}

int main() {

    // various initializations and error checking
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "3DEngine", nullptr, nullptr);
    if (window == nullptr) {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    // GLFW's OpenGL viewport configuration
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

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

    // To implement in a "Camera" class

    glm::mat4 projection = glm::perspective
    (
        glm::radians(45.0f),  // field of view
        (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,    // aspect ratio
        0.1f,                 // near plane
        100.0f                // far plane
    );

    TexturedMonkey.useShader();
    unsigned int TexturedMonkey_Shader_ID = TexturedMonkey.getShader_ID();
    glUniformMatrix4fv(glGetUniformLocation(TexturedMonkey_Shader_ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    
    VertexColoursMonkey.useShader();
    unsigned int VertexColoursMonkey_Shader_ID = VertexColoursMonkey.getShader_ID();    
    glUniformMatrix4fv(glGetUniformLocation(VertexColoursMonkey_Shader_ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));


    unsigned int Teapot_Shader_ID = Teapot.getShader_ID();
    Teapot.useShader();
    glUniformMatrix4fv(glGetUniformLocation(Teapot_Shader_ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    // Main render loop
    glEnable(GL_DEPTH_TEST);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // glPointSize(5);
    // glLineWidth(5);

    glEnable(GL_CULL_FACE);

    glm::vec3 lightPos = glm::vec3(-1.5, 0.0, 0.5);

    while (!glfwWindowShouldClose(window)) {
        // Scene setup
        // timer.advanceTime();
        float currentTime = glfwGetTime();
        deltaTime = currentTime - previousTime;
        previousTime = currentTime;

        // input
        processInput(window);

        // rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view = glm::lookAt
        (
            cameraPos,
            cameraPos + cameraFront,
            cameraUp
        );

        // Manually testing the view matrices here (will be implemented in Camera class)
        TexturedMonkey.useShader();
        TexturedMonkeyShader.setMat4("view", view);
        TexturedMonkeyShader.setVec3("cameraViewPos", cameraPos);
        TexturedMonkeyShader.setVec3("lightPos", lightPos);
        
        VertexColoursMonkey.useShader();
        VertexColoursMonkeyShader.setMat4("view", view);
        VertexColoursMonkeyShader.setVec3("cameraViewPos", cameraPos);
        VertexColoursMonkeyShader.setVec3("lightPos", lightPos);

        Teapot.useShader();
        TeapotShader.setMat4("view", view);
        TeapotShader.setVec3("cameraViewPos", cameraPos);
        TeapotShader.setVec3("lightPos", lightPos);

        // Note for later: Standardize it with the timer class to properly make use of deltaTime
        // TexturedMonkey.Rotate(0.0, 0.0, 0.0);
        TexturedMonkey.Draw();

        // VertexColoursMonkey.SetPosition(0, cos((float)glfwGetTime()), -3);
        VertexColoursMonkey.Rotate(0.0, 0.5, 0.2*sin(glfwGetTime()));
        VertexColoursMonkey.Draw();

        Teapot.Translate(0.0, 0.0, 0.01*sin(glfwGetTime()));
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