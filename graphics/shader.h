#ifndef RPP_SHADER_H
#define RPP_SHADER_H

#include "shader_data.hpp"

#include "glm/glm.hpp"
#include "glad/gl.h"

#include <map>
#include <string>
#include <memory>

using glm::mat4;

struct ShaderData;

struct Shader {
    unsigned int handle = 0;
    int mvpLocation = -1;

    explicit Shader(const ShaderData &shaderData );
    ~Shader();

    void SetMvpUniform(const mat4 &mvp) const;
    void Bind() const;

    static void validateShader(unsigned int shader);
    static unsigned int compileShader(const char* source, GLenum type);
    static void validateProgram(unsigned int shaderProgram);
    static unsigned int linkProgram(unsigned int vertexShader, unsigned int fragmentShader);
};

#endif // RPP_SHADER_H
