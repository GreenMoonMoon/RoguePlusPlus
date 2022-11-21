#include "flecs.h"
#include "graphics/renderer.h"
#include "inputs/inputs.h"

#include "graphics/texture.h"
#include "graphics/mesh.h"
#include "graphics/camera.h"
#include "graphics/shader.h"

#include "components/tile.hpp"

#include "glm/glm.hpp"

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

    world.emplace<Camera>(glm::vec2(720.0f, 576.0f) * 0.02857f);

    // DEBUG PARTICLE
    world.scope<ParticleScope>([](){
        world.entity()
        .set<Particle>({glm::vec2(1.0f), glm::vec2(0.0f, 20.0f), glm::vec2(0.0f)})
        .add<Sprite>();
    });
    // DEBUG

    world.set<Input>({});
    world.system<Input>("Input")
            .kind(flecs::PreUpdate)
            .each([](Input &input){
                input.ProcessEvents(isRunning);
            });

    world.system<Particle>()
            .kind(flecs::OnUpdate)
            .each([](flecs::iter &it, size_t, Particle &particle){
                particle.position += particle.velocity * it.world().delta_time();
            });

    world.system<const Particle, const Sprite, const Camera>()
            .term_at(3).singleton()
            .kind(flecs::OnStore)
            .each([&](const Particle &particle, const Sprite &sprite, const Camera &camera){
                glm::mat4 transform = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
                transform = glm::translate(transform, glm::vec3(particle.position, 0.0f));
                renderer.DrawSprite(transform, camera.view, sprite, shader);
            });

    auto tile = world.entity();
    tile.add<Tile>();

    while(isRunning) {
        renderer.Clear();
        world.progress(renderer.GetDeltaTime());
        renderer.Present();
    }

    return 0;
}
