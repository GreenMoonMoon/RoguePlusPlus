#include "shader.h"
#include "glm/gtc/type_ptr.hpp"

#include <iostream>

void Shader::validateShader(unsigned int shader) {
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "Error compiling shader:\n\t" << infoLog << std::endl;
    }
}

unsigned int Shader::compileShader(const char* source, GLenum type) {
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    validateShader(shader);

    return shader;
}

void Shader::validateProgram(unsigned int shaderProgram) {
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "Error linking shader program:\n\t" << infoLog << std::endl;
    }
}

unsigned int Shader::linkProgram(const unsigned int vertexShader, const unsigned int fragmentShader) {
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    validateProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

Shader::Shader(const ShaderData &shaderData) {
    unsigned int vertexShader = Shader::compileShader(shaderData.vertexSource, GL_VERTEX_SHADER);
    unsigned int fragmentShader = Shader::compileShader(shaderData.fragmentSource, GL_FRAGMENT_SHADER);
    handle = Shader::linkProgram(vertexShader, fragmentShader);
    mvpLocation = glGetUniformLocation(handle, "mvp");
}

Shader::~Shader() {
    glDeleteProgram(handle);
}

void Shader::SetMvpUniform(const mat4 &mvp) const {
    glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(mvp));
}

void Shader::Bind() const {
    glUseProgram(handle);
}
