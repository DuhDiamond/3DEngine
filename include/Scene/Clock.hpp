#ifndef CLOCK_HPP
#define CLOCK_HPP

// To implement later as a wrapper of glfwGetTime() to standardize global time around

class Clock
{
private:
    double time = 0;
public:
    double advanceTime();
    double deltaTime();
};

#endif