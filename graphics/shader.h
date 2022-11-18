#ifndef RPP_SHADER_H
#define RPP_SHADER_H

#include "glm/glm.hpp"
#include "glad/gl.h"

#include <map>
#include <string>
#include <memory>

using glm::mat4;

enum class ShadingType {
    DEBUG,
    BASIC,
    BASIC_DIFFUSE,
};

struct ShaderData {
    ShadingType type = ShadingType::BASIC_DIFFUSE;

    const char *vertexSource;
    const char *fragmentSource;
};

struct Shader {
    unsigned int handle;
    int mvpLocation;

    static std::map<ShadingType, std::shared_ptr<Shader>> shaders;

    Shader(unsigned int handle = 0, int mvpLocation = -1) : handle(handle), mvpLocation(mvpLocation) {};
    ~Shader();

    static std::shared_ptr<Shader> Load(const ShaderData &shaderData);

    void SetMvpUniform(const mat4 &mvp) const;
    void Use() const;

    static void validateShader(unsigned int shader);
    static unsigned int compileShader(const char* source, GLenum type);
    static void validateProgram(unsigned int shaderProgram);
    static unsigned int linkProgram(const unsigned int vertexShader, const unsigned int fragmentShader);
};

#endif // RPP_SHADER_H
