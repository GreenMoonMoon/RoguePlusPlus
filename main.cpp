#include <iostream>

#include "flecs.h"
#include "graphics/renderer.h"
#include "inputs/inputs.h"

#include "graphics/mesh.h"
#include "graphics/camera.h"
#include "graphics/shader_data.h"

#include "components/tile.hpp"

#include "glm/glm.hpp"

using glm::vec2;

bool isRunning = true;
flecs::world world;

int main(int argc, char **argv) {
    Renderer renderer;
    Mesh mesh = Mesh(MeshData::Quad);
    Shader shader = Shader(ShaderData::Debug);

    TextureData textureData {"C:/Users/josue/Projects/rpp/assets/kenney_physic_pack/PNG/Wood elements/elementWood010.png"};
    Texture texture = Texture(textureData);

    world.emplace<Camera>(vec2(720.0f, 576.0f) * 0.02857f);

    world.set<Input>({});
    world.system<Input>("Input")
            .kind(flecs::PreUpdate)
            .each([](Input &input){
                input.ProcessEvents(isRunning);
            });

    world.system<const Tile, const Camera>()
            .term_at(2).singleton()
            .kind(flecs::OnStore)
            .each([&](const Tile &tile, const Camera &camera){
                renderer.Draw(camera, mesh, shader, texture);
            });

    auto tile = world.entity();
    tile.add<Tile>();

    while(isRunning) {
        renderer.Clear();
        world.progress();
        renderer.Present();
    }

    return 0;
}
