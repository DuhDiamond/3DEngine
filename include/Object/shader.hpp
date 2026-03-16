#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

// Will figure out more about how to integrate this into the new reorganized class structure later on, once I get texture handling working
class shader
{
private:
    unsigned int SHADER_ID;
public:
    unsigned int getShaderID();
    void loadShader(const char* vertexPath, const char* fragmentPath);
    void use();

    void setBool(const string &name, bool value) const;
    void setInt(const string &name, int value) const;
    void setFloat(const string &name, float value) const;
    ~shader();
};

#endif