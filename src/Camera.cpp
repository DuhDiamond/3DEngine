#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Scene/Camera.hpp"

unsigned int Camera::SCREEN_WIDTH = 1920;
unsigned int Camera::SCREEN_HEIGHT = 1080;

float Camera::cameraSpeed = 2.0;
float Camera::sensitivity = 0.001;

bool Camera::firstMouse = true;
float Camera::previous_xPos = (float)Camera::SCREEN_WIDTH/2.0;
float Camera::previous_yPos = (float)Camera::SCREEN_HEIGHT/2.0;

float Camera::deltaTime = 0.0;
float Camera::previousTime = 0.0;

void Camera::initializeViewport() {
    SCREEN_WIDTH = 1920;
    SCREEN_HEIGHT = 1080;

    cameraSpeed = 2.0;
    sensitivity = 0.001;

    firstMouse = true;
    previous_xPos = (float)getWidth()/2.0;
    previous_yPos = (float)getHeight()/2.0;

    deltaTime = 0.0;
    previousTime = 0.0;
}

void Camera::initializeCamera() {
    yaw = -90.0;
    pitch = 0.0;


    cameraPos = glm::vec3(0.0, 0.0, 3.0);
    cameraFront = glm::vec3(0.0, 0.0, -1.0);
    cameraUp = glm::vec3(0.0, 1.0, 0.0);

    view = glm::lookAt
    (
        cameraPos,
        cameraPos + cameraFront,
        cameraUp
    );
    projection = glm::perspective
    (
        glm::radians(45.0f),                      // field of view
        (float)getWidth() / (float)getHeight(),   // aspect ratio
        0.1f,                                     // near plane
        100.0f                                    // far plane
    );
}


// I have no clue why, but declaring the variables like this lets me return without error, otherwise compiler complains
unsigned int Camera::getWidth() {
    return SCREEN_WIDTH;
}
unsigned int Camera::getHeight() { 
    return SCREEN_HEIGHT;
}

void Camera::mouse_callback(GLFWwindow* window, double xPos, double yPos) {
    if (firstMouse) {
        previous_xPos = xPos;
        previous_yPos = yPos;
        firstMouse = false;
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

void Camera::updateViewMatrix() {
    view = glm::lookAt
    (
        cameraPos,
        cameraPos + cameraFront,
        cameraUp
    );
}

void Camera::processInput(GLFWwindow* window)
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