#include "Object/Material/shader.hpp"

using namespace std;

shader::shader(const char* vertexPath, const char* fragmentPath) {
    string vertexCode, fragmentCode;
    ifstream vShaderFile, fShaderFile;

    // Ensures the ifstreams can throw exceptions
    vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
    fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);

    try {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);

        stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode =    vShaderStream.str();
        fragmentCode =  fShaderStream.str();

    } catch (ifstream::failure e) {
        cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << endl;
        if (!vShaderFile) {
            perror("open failure for vertex shader: ");
        }
        if (!fShaderFile) {
            perror("open failure for fragment shader: ");
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
    Shader_ID = glCreateProgram();
    glAttachShader(Shader_ID, vertexShader);
    glAttachShader(Shader_ID, fragmentShader);
    glLinkProgram(Shader_ID);
    
    glGetProgramiv(Shader_ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(Shader_ID, 512, nullptr, infoLog);
        cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
    }

    // Freeing memory after linking
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void shader::use() {
    glUseProgram(Shader_ID);
}

void shader::setBool(const string &name, bool value) const {
    glUniform1i(glGetUniformLocation(Shader_ID, name.c_str()), (int)value);
}

void shader::setInt(const string &name, int value) const {
    glUniform1i(glGetUniformLocation(Shader_ID, name.c_str()), value);
}

void shader::setFloat(const string &name, float value) const {
    glUniform1f(glGetUniformLocation(Shader_ID, name.c_str()), value);
}

shader::~shader() {
    glDeleteProgram(Shader_ID);
}