#ifndef RPP_SHADER_H
#define RPP_SHADER_H

#include "glm/glm.hpp"
#include "glad/gl.h"

#include <map>
#include <string>
#include <memory>

using glm::mat4;

struct ShaderData {
    const char *vertexSource;
    const char *fragmentSource;

    static ShaderData Debug;
    static ShaderData Basic;
    static ShaderData BasicDiffuse;
};

struct Shader {
    unsigned int handle = 0;
    int mvpLocation = -1;

    explicit Shader(const ShaderData &shaderData );
    ~Shader();

    void SetMvpUniform(const mat4 &mvp) const;
    void Use() const;

    static void validateShader(unsigned int shader);
    static unsigned int compileShader(const char* source, GLenum type);
    static void validateProgram(unsigned int shaderProgram);
    static unsigned int linkProgram(unsigned int vertexShader, unsigned int fragmentShader);
};

#endif // RPP_SHADER_H
