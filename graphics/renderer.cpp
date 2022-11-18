#include "renderer.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "camera.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <iostream>

using glm::vec4;

GLenum glCheckError_(const char* file, int line) {
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR) {
        const char* error;
        switch (errorCode) {
            case GL_INVALID_ENUM:
                error = "INVALID_ENUM";
                break;
            case GL_INVALID_VALUE:
                error = "INVALID_VALUE";
                break;
            case GL_INVALID_OPERATION:
                error = "INVALID_OPERATION";
                break;
            case GL_STACK_OVERFLOW:
                error = "STACK_OVERFLOW";
                break;
            case GL_STACK_UNDERFLOW:
                error = "STACK_UNDERFLOW";
                break;
            case GL_OUT_OF_MEMORY:
                error = "OUT_OF_MEMORY";
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                error = "INVALID_FRAMEBUFFER_OPERATION";
                break;
        }
        std::cerr << error << '|' << file << '|' << line << std::endl;
    }
    return errorCode;
}

void debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const char* message, const void *parameters) {
    const GLubyte *sourceStr = glGetString(source);
    const GLubyte *typeStr = glGetString(type);
    const GLubyte *severityStr = glGetString(severity);

    if(sourceStr and typeStr and severityStr) {
        std::cerr << sourceStr << ':' << typeStr << '[' << severityStr << ']' << id << ": "
                  << message << std::endl;
    } else {
        std::cerr << id << " " << message << std::endl;
    }
}

SDLRenderer::SDLRenderer(int width, int height) {
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL2 video subsystem couldn't be initialized. Error: " << SDL_GetError()
                  << std::endl;
        return;
    }

    window = SDL_CreateWindow("Rogue++", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width,
                              height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == nullptr) {
        std::cerr << "SDL2 Renderer couldn't be created. Error: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG); //DEBUG

    context = SDL_GL_CreateContext(window);

    int version = gladLoadGL((GLADloadfunc) SDL_GL_GetProcAddress);
    if (version == 0) {
        std::cout << "Failed to initialize OpenGL context\n" << std::endl;
        return;
    }

    // DEBUG
    glDebugMessageCallback(debugCallback, nullptr);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);

    const GLubyte *glRenderer = glGetString(GL_RENDERER);
    const GLubyte *glVendor = glGetString(GL_VENDOR);
    const GLubyte *glVersion = glGetString(GL_VERSION);
    const GLubyte *glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);

    std::cout << "GL Renderer: " << glRenderer << std::endl;
    std::cout << "GL Vendor: " << glVendor << std::endl;
    std::cout << "GL Version: " << glVersion << std::endl;
    std::cout << "GL GLSL: " << glslVersion << std::endl;

//    glEnable(GL_DEPTH_TEST);
}

SDLRenderer::~SDLRenderer() {
    SDL_GL_DeleteContext(context);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}

void SDLRenderer::Clear() const {
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void SDLRenderer::Present() const {
    SDL_GL_SwapWindow(window);
}

void SDLRenderer::Draw(const Camera &camera, const Mesh &mesh, const Shader &shader, const Texture &texture) const {
    mesh.Bind();
    glCheckError();
    shader.Bind();
    glCheckError();
    texture.Bind(0);
    glCheckError();

    shader.SetMvpUniform(camera.view);
    glCheckError();
    glDrawElements(GL_TRIANGLES, mesh.triangleCount, GL_UNSIGNED_INT, 0);
    glCheckError();
}
