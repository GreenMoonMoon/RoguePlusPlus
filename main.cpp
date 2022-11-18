#include <iostream>

#include "flecs.h"
#include "graphics/renderer.h"
#include "inputs/inputs.h"

#include "graphics/mesh.h"
#include "graphics/model.h"
#include "graphics/camera.h"
#include "graphics/shader_data.h"

#include "glm/glm.hpp"

using glm::vec2;

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
    m.Load({{"C:/Users/josue/Projects/rpp/assets/kenney_physic_pack/PNG/Wood elements/elementWood010.png"},
            Quad,
            DebugShader});

    auto cam = Camera(vec2(720.0f, 576.0f) * 0.02857f);

    while(isRunning) {
        renderer.Clear();

        world.progress();
        m.Draw(cam, renderer);

        renderer.Present();
    }

    return 0;
}
