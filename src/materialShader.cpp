#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Object/materialShader.hpp"

using namespace std;

unsigned int materialShader::getShader_ID()
{
    return SHADER_ID;
}

void materialShader::loadShader(const char* vertexPath, const char* fragmentPath)
{
    string vertexCode, fragmentCode;
    ifstream vShaderFile, fShaderFile;

    vShaderFile.open(vertexPath);
    vShaderFile.exceptions(ifstream::badbit | ifstream::failbit);

    fShaderFile.open(fragmentPath);
    fShaderFile.exceptions(ifstream::badbit | ifstream::failbit);

    if (vShaderFile.is_open() && fShaderFile.is_open()) {
        try {
            stringstream vShaderStream, fShaderStream;
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();

            vShaderFile.close();
            fShaderFile.close();

            vertexCode =    vShaderStream.str();
            fragmentCode =  fShaderStream.str();
        } catch (exception &e) {
            cout << "ERROR: Shader file(s) not successfully read:" << endl;
            if (vShaderFile.badbit)  perror("vShaderFile: badbit (read/write error on i/o)");
            if (vShaderFile.failbit) perror("vShaderFile: failbit (logic error on i/o)");
            
            if (fShaderFile.badbit)  perror("fShaderFile: badbit (read/write error on i/o)");
            if (fShaderFile.failbit) perror("fShaderFile: failbit (logic error on i/o)");
            
            cout << "Information: " << e.what() << endl;
        }
    } else {
        cout << "Error: Shader file(s) not successfully opened" << endl;
        if (!vShaderFile) {
            perror("Open failure for vertex shader");
        }
        if (!fShaderFile) {
            perror("Open failure for fragment shader");
        }
    }

    const char* vertexShaderCode = vertexCode.c_str();
    const char* fragmentShaderCode = fragmentCode.c_str();


    unsigned int vertexShader, fragmentShader;
    int success;
    char infoLog[512];

    // vertex shader handling
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderCode, nullptr);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
    }

    // fragment shader handling
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
    }

    // Linking to ID of this given class instance
    SHADER_ID = glCreateProgram();
    glAttachShader(SHADER_ID, vertexShader);
    glAttachShader(SHADER_ID, fragmentShader);
    glLinkProgram(SHADER_ID);
    
    glGetProgramiv(SHADER_ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(SHADER_ID, 512, nullptr, infoLog);
        cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
    }

    // Freeing memory after linking
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void materialShader::useShader() {
    glUseProgram(SHADER_ID);
}

void materialShader::setBool(const string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(SHADER_ID, name.c_str()), (int)value);
}

void materialShader::setInt(const string &name, int value) const
{
    glUniform1i(glGetUniformLocation(SHADER_ID, name.c_str()), value);
}

void materialShader::setFloat(const string &name, float value) const
{
    glUniform1f(glGetUniformLocation(SHADER_ID, name.c_str()), value);
}

void materialShader::setVec3(const string &name, glm::vec3 value) const
{
    glUniform3f(glGetUniformLocation(SHADER_ID, name.c_str()), value.x, value.y, value.z);
}

void materialShader::setMat4(const string &name, glm::mat4 value) const
{
    glUniformMatrix4fv(glGetUniformLocation(SHADER_ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

materialShader::~materialShader()
{
    glDeleteProgram(SHADER_ID);
}