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

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
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

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    // GLFW's OpenGL viewport configuration
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    
    // To handle window resizing
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


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
    TexturedMonkey.Instantiate();
    TexturedMonkey.SetSize(1, 1, 1);


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

    VertexColoursMonkey.Instantiate();
    VertexColoursMonkey.SetSize(2.5, 2.5, 2.5);

    // The Teapot Object

    // Note: I don't actually use the UV map on this object at the moment
    ObjMesh TeapotMesh;
    TeapotMesh.loadMesh("../Meshes/teapotTriangulatedUVMapped.obj");

    materialShader TeapotShader;
    TeapotShader.loadShader(PhongVertexShader, VertexColoursPhongFragmentShader);
    
    Object Teapot;
    Teapot.Attach(&TeapotMesh);
    // Showing how Materials can also be reused;
    // this will just draw the Teapot's vertex colours instead, however, since the Teapot .obj has no colours,
    // the buffer loads to the fallback (0.5, 0.5, 0.5) grey colour for every corresponding vertex
    // Thus, the object will render a default grey colour
    Teapot.Attach(&VertexColoursMonkeyMaterial);

    Teapot.Instantiate();
    Teapot.SetSize(0.5, 1, 0.5);
    Teapot.Translate(-5, -3, -3);



    // To implement in a "Camera" class
    glm::mat4 view = glm::lookAt
    (
        glm::vec3(0.0f, 2.0f, 10.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );

    glm::mat4 projection = glm::perspective
    (
        glm::radians(45.0f),  // field of view
        1920.0f / 1080.0f,      // aspect ratio
        0.1f,                 // near plane
        100.0f                // far plane
    );


    // Manually testing the view/projection matrices here (will be implemented in Camera class)
    unsigned int TexturedMonkey_Shader_ID = TexturedMonkey.getShader_ID();
    TexturedMonkey.useShader();

    glUniformMatrix4fv(glGetUniformLocation(TexturedMonkey_Shader_ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(TexturedMonkey_Shader_ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));


    unsigned int VertexColoursMonkey_Shader_ID = VertexColoursMonkey.getShader_ID();
    VertexColoursMonkey.useShader();

    glUniformMatrix4fv(glGetUniformLocation(VertexColoursMonkey_Shader_ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(VertexColoursMonkey_Shader_ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));


    unsigned int Teapot_Shader_ID = Teapot.getShader_ID();
    Teapot.useShader();

    glUniformMatrix4fv(glGetUniformLocation(Teapot_Shader_ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(Teapot_Shader_ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));



    // Main render loop
    glEnable(GL_DEPTH_TEST);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPointSize(5);
    glLineWidth(5);

    glEnable(GL_CULL_FACE);

    while (!glfwWindowShouldClose(window)) {
        // Scene setup
        // timer.advanceTime();

        // input
        processInput(window);

        // rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Note for later: Standardize it with the timer class to properly make use of deltaTime
        TexturedMonkey.Rotate(0, sin(1), 0);
        TexturedMonkey.SetPosition(sin((float)glfwGetTime()), sin((float)glfwGetTime()), sin((float)glfwGetTime()));
        TexturedMonkey.Draw();

        VertexColoursMonkey.SetPosition(0, cos((float)glfwGetTime()), -3);
        VertexColoursMonkey.Rotate(0, sin(0.1), 0);
        VertexColoursMonkey.Draw();

        Teapot.Rotate(0, sin(0.2), 0);
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