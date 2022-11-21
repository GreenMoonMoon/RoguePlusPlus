#ifndef RPP_SHADER_H
#define RPP_SHADER_H

#include "shader_data.hpp"

#include "glm/glm.hpp"
#include "glad/gl.h"

#include <map>
#include <string>
#include <memory>

struct ShaderData;

struct Shader {
    unsigned int handle = 0;
    int transformLocation = -1;
    int cameraLocation = -1;

    explicit Shader(const ShaderData &shaderData );
    ~Shader();

    void SetTransformUniform(const glm::mat4 &transform) const;
    void SetCameraUniform(const glm::mat4 &camera) const;
    void Bind() const;

    static void validateShader(unsigned int shader);
    static unsigned int compileShader(const char* source, GLenum type);
    static void validateProgram(unsigned int shaderProgram);
    static unsigned int linkProgram(unsigned int vertexShader, unsigned int fragmentShader);
};

#endif // RPP_SHADER_H
