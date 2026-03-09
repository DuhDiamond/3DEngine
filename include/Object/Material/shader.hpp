#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

// Will figure out more about how to integrate this into the new reorganized class structure later on, once I get texture handling working
class shader {
public:
    unsigned int Shader_ID;

    shader(const char* vertexPath, const char* fragmentPath);
    ~shader();

    void use();
    void setBool(const string &name, bool value) const;
    void setInt(const string &name, int value) const;
    void setFloat(const string &name, float value) const;
};

#endif