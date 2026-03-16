#include "Object/shader.hpp"

using namespace std;

unsigned int shader::getShaderID()
{
    return SHADER_ID;
}

void shader::loadShader(const char* vertexPath, const char* fragmentPath)
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

void shader::use()
{
    glUseProgram(SHADER_ID);
}

void shader::setBool(const string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(SHADER_ID, name.c_str()), (int)value);
}

void shader::setInt(const string &name, int value) const
{
    glUniform1i(glGetUniformLocation(SHADER_ID, name.c_str()), value);
}

void shader::setFloat(const string &name, float value) const
{
    glUniform1f(glGetUniformLocation(SHADER_ID, name.c_str()), value);
}

shader::~shader()
{
    glDeleteProgram(SHADER_ID);
}