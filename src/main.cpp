#include <iostream>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stb/stb_image.h>

#include "Object/shader.hpp"
#include "Object/ObjMesh.hpp"
#include "Object/Object.hpp"
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


    // Will need to abstract away this logic later; currently set up for testing
    // Currently, to call "Instantiate", you will need at minimum a ObjMesh attached,
    // but a shader is also necessary for it to render
    // Texture is not currently used in this setup (texture loads, but does not align to
    // texture coordinates as expected)

    ObjMesh mesh;
    mesh.loadMesh("Meshes/suzanneTriangulated.obj");
    mesh.buildBuffer();

    Object Object1;
    Object1.Attach(&mesh);

    const char* vertexShader1 = "../shaders/vertex1.glsl";
    const char* fragShader1 =   "../shaders/fragment1.glsl";
    shader Object1Shader;
    Object1Shader.loadShader(vertexShader1, fragShader1);
    Object1.Attach(&Object1Shader);

    Object1.Instantiate();

    unsigned int Texture_ID;
    
    glGenTextures(1, &Texture_ID);
    glBindTexture(GL_TEXTURE_2D, Texture_ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char *data = stbi_load("../textures/suzanneTexture.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        cout << "Failed to load texture" << endl;
    }
    stbi_image_free(data);

    glm::mat4 view = glm::lookAt
    (
        glm::vec3(0.0f, 2.0f, 10.0f),
        glm::vec3(0.0f, 1.5f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );

    glm::mat4 projection = glm::perspective
    (
        glm::radians(45.0f),  // field of view
        800.0f / 600.0f,      // aspect ratio
        0.1f,                 // near plane
        100.0f                // far plane
    );


    // Manually testing the model/view/projection matrices here (will be implemented in Object class)
    unsigned int Shader_ID = Object1.getShaderID();
    Object1.useShader();

    glUniformMatrix4fv(glGetUniformLocation(Shader_ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(Shader_ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));


    // Main render loop
    glEnable(GL_DEPTH_TEST);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPointSize(5);
    glLineWidth(5);

    glEnable(GL_CULL_FACE);

    while (!glfwWindowShouldClose(window)) {
        
        // input
        processInput(window);

        // rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 1.0f, 1.0f));
        
        unsigned int modelLocation = glGetUniformLocation(Shader_ID, "model");
        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

        Object1.useShader();
        glBindVertexArray(Object1.getVAO_ID());
        glBindTexture(GL_TEXTURE_2D, Texture_ID);
        // glBindBuffer(GL_ARRAY_BUFFER, myObject.getVBO_ID());
        glDrawElements(GL_TRIANGLES, mesh.getEBOSize(), GL_UNSIGNED_INT, 0);
        // glDrawArrays(GL_TRIANGLES, 0, mesh.getBufferSize() / 11);

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