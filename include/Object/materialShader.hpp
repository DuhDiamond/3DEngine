#ifndef MATERIALSHADER_H
#define MATERIALSHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class materialShader
{
private:
    unsigned int SHADER_ID;
public:
    unsigned int getShader_ID();
    void loadShader(const char* vertexPath, const char* fragmentPath);
    void useShader();

    void setBool(const string &name, bool value) const;
    void setInt(const string &name, int value) const;
    void setFloat(const string &name, float value) const;
    ~materialShader();
};

#endif