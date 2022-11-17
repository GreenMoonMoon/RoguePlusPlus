#include <iostream>

#include "flecs.h"
#include "graphics/renderer.h"
#include "inputs/inputs.h"

#include "graphics/mesh.h"

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


    //Debug
    // TODO: review this encapsulation, there is a better way to load builtin geo that could
    //  be done in a single step
    Mesh quad;
    quad.Load(Quad);


    while(isRunning) {
        renderer.Clear();
        world.progress();

        renderer.RenderMesh(quad); //TODO: change name to draw

        renderer.Present();
    }

    return 0;
}
