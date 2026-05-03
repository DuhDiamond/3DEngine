#ifndef CAMERA_HPP
#define CAMERA_HPP

class Camera {
private:
    static unsigned int SCREEN_WIDTH;
    static unsigned int SCREEN_HEIGHT;
    static float cameraSpeed;
    static float sensitivity;
    static bool firstMouse;

    // Program starts at center of the screen
    static float previous_xPos;
    static float previous_yPos;
public:
    static float deltaTime;
    static float previousTime;

    static void initializeViewport();

    static unsigned int getWidth();
    static unsigned int getHeight();
    static unsigned int activeCamera; // This denotes which camera in a scene is active (if there exist multiple)

    void initializeCamera();
    float yaw;
    float pitch;

    void mouse_callback(GLFWwindow* window, double xPos, double yPos);
    void updateViewMatrix();
    void processInput(GLFWwindow* window);

    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;

    glm::mat4 view;
    glm::mat4 projection;
};

#endif