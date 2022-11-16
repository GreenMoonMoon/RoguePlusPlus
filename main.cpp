#include <iostream>

#include "flecs.h"
#include "graphics/renderer.h"
#include "inputs/inputs.h"

bool isRunning = true;
flecs::world world;

int main(int argc, char **argv) {
    Renderer renderer;

    world.set<Input>({});
    world.system<Input>("Input")
            .kind(flecs::PreUpdate)
            .each([](Input &input){
                input.ProcessEvents(isRunning);
            });

    while(isRunning) {
        renderer.Clear();
        world.progress();

        renderer.Present();
    }

    return 0;
}
