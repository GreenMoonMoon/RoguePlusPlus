#include "flecs.h"
#include "graphics/renderer.h"
#include "inputs/inputs.h"

#include "graphics/texture.h"
#include "graphics/mesh.h"
#include "graphics/camera.h"
#include "graphics/shader.h"

#include "components/tile.hpp"

#include "glm/glm.hpp"

using glm::vec2;

bool isRunning = true;
flecs::world world;

int main(int argc, char **argv) {
    Renderer renderer;
//    Mesh mesh = Mesh(MeshData::Quad);
//    Shader shader = Shader(ShaderData::Debug);
//    TextureData textureData {"C:/Users/josue/Projects/rpp/assets/kenney_physic_pack/PNG/Wood elements/elementWood010.png"};
//    Texture texture = Texture(textureData);

    ShaderData shaderData;
    shaderData.LoadFromFiles("C:/Users/josue/Projects/rpp/assets/shaders/point_shader.vert",
                             "C:/Users/josue/Projects/rpp/assets/shaders/point_shader.frag");
    Shader   shader = Shader(shaderData);

    world.emplace<Camera>(vec2(720.0f, 576.0f) * 0.02857f);

    // DEBUG PARTICLE
    world.scope<ParticleScope>([](){
        world.entity()
        .add<Particle>()
        .add<Sprite>();
    });
    // DEBUG

    world.set<Input>({});
    world.system<Input>("Input")
            .kind(flecs::PreUpdate)
            .each([](Input &input){
                input.ProcessEvents(isRunning);
            });

    world.system<const Particle, const Sprite, const Camera>()
            .term_at(3).singleton()
            .kind(flecs::OnStore)
            .each([&](const Particle &particle, const Sprite &sprite, const Camera &camera){
//                renderer.Draw(camera, mesh, shader, texture);
                renderer.DrawSprite(camera, sprite, shader);
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
