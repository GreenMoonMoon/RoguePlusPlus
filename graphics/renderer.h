#ifndef RPP_RENDERER_H
#define RPP_RENDERER_H

#include "glad/gl.h"
#include "SDL.h"

struct Mesh;
struct Shader;
struct Texture;
struct Camera;

struct SDLRenderer {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_GLContext context;

    SDLRenderer() : SDLRenderer(720, 576) {};
    SDLRenderer(int width, int height);
    ~SDLRenderer();

    void Clear() const;
    void Present() const;

    void Draw(const Camera &camera, const Mesh &mesh, const Shader &shader, const Texture &texture) const;
    void DrawPoints(const Camera &camera, const Mesh &mesh, const Shader &shader);
};

#ifdef SDL_OPENGL_GRAPHICS
using Renderer = SDLRenderer;
#endif

GLenum glCheckError_(const char* file, int line);
#define glCheckError() glCheckError_(__FILE__, __LINE__)

#endif // RPP_RENDERER_H