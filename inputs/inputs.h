#ifndef SM64_INPUTS_H
#define SM64_INPUTS_H

#include "SDL.h"
#include "controller.h"

struct Input {
    SDL_Event event;
    std::vector<Gamepad *> gamepads;

    Input();
    ~Input() = default;

    void ProcessEvents(bool &running);
};

#endif // SM64_INPUTS_H
