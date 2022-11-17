#include <iostream>

#include "flecs.h"
#include "graphics/renderer.h"
#include "inputs/inputs.h"

#include "graphics/mesh.h"
#include "graphics/model.h"
#include "graphics/textures.h"
#include "graphics/shader_data.h"

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

    //DEBUG
    Model m;
    m.Load({{"C:/Users/josue/Projects/rpp/assets/kenney_physic_pack/PNG/Wood elements/elementWood013.png"},
            Quad,
            DebugShader});

    while(isRunning) {
        renderer.Clear();
        world.progress();

        m.Draw(camera, renderer);

        renderer.Present();
    }

    return 0;
}
