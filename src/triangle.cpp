float vertices1[] = {
    0.5f, 0.5f, 0.0f,   0.5f, 0.6f, 0.9f,
    0.5f, -0.5f, 0.0f,  0.1f, 0.3f, 0.4f,
    -0.5f, -0.5f, 0.0f, 0.5f, 0.1f, 0.2f,
    -0.5f, 0.5f, 0.0f,  0.2f, 0.3f, 0.4f

};
unsigned int indices1[] = {
    0, 1, 3,
    1, 2, 3
};

float vertices2[] = {
    // Positions        // Colours
    1.0f, 1.0f, 0.0f,   1.0f, 0.0f, 0.0f,
    0.5f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f,
    1.0f, 0.5f, 0.0f,   0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.0f,   0.0f, 0.5f, 1.0f
};
unsigned int indices2[] {
    0, 1, 2,
    1, 2, 3
};