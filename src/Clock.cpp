#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Scene/Clock.hpp"

double Clock::advanceTime() { return (time += deltaTime()); }

double Clock::deltaTime() {
    double oldTime = time;
    double newTime = glfwGetTime();
    return (newTime - oldTime);
}