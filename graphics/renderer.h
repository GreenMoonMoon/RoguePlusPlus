#ifndef RPP_RENDERER_H
#define RPP_RENDERER_H

#include "glad/gl.h"
#include "SDL.h"
#include "glm/glm.hpp"

struct Mesh;
struct Sprite;
struct Shader;
struct Texture;
struct Camera;

struct SDLRenderer {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_GLContext context;
    uint32_t previousTime = 0;
    double DeltaTime = 0;

    SDLRenderer() : SDLRenderer(720, 576) {};
    SDLRenderer(int width, int height);
    ~SDLRenderer();

    void Clear() const;
    void Present() const;

    void DrawSprite(const glm::mat4 &transform, const glm::mat4 &camera, const Sprite &sprite, const Shader &shader) const;

    void UpdateTime();
};

#ifdef SDL_OPENGL_GRAPHICS
using Renderer = SDLRenderer;
#endif

GLenum glCheckError_(const char* file, int line);
#define glCheckError() glCheckError_(__FILE__, __LINE__)

#endif // RPP_RENDERER_H