#ifndef SM64_RENDERER_H
#define SM64_RENDERER_H

#include "glad/gl.h"
#include "SDL.h"


struct SDLRenderer {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_GLContext context;

    SDLRenderer() : SDLRenderer(720, 576) {};
    SDLRenderer(int width, int height);
    ~SDLRenderer();

    void Clear() const;
    void Present() const;

    void RenderMesh(const struct Mesh &mesh);
};

#ifdef SDL_OPENGL_GRAPHICS
using Renderer = SDLRenderer;
#endif

#endif // SM64_RENDERER_H