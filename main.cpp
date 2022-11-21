#include "flecs.h"
#include "graphics/renderer.h"
#include "inputs/inputs.h"

#include "graphics/texture.h"
#include "graphics/mesh.h"
#include "graphics/camera.h"
#include "graphics/shader.h"

#include "components/tile.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

bool isRunning = true;
flecs::world world;

int main(int argc, char **argv) {
    Renderer renderer;

    ShaderData shaderData;
    shaderData.LoadFromFiles("C:/Users/josue/Projects/rpp/assets/shaders/point_shader.vert",
                             "C:/Users/josue/Projects/rpp/assets/shaders/point_shader.frag");
    Shader   shader = Shader(shaderData);

    world.emplace<Camera>(glm::vec2(720.0f, 576.0f), 0.01f);

    world.scope<ParticleScope>([](){
        world.entity()
        .set<Particle>({glm::vec2(720.0f, 576.0f) * 0.01f * 0.5f, glm::vec2(0.0f), glm::vec2(0.0f, -9.8f)})
        .add<Sprite>();
    });

    world.set<Input>({});
    world.system<Input>("Input")
            .kind(flecs::PreUpdate)
            .each([](Input &input){
                input.ProcessEvents(isRunning);
            });

    world.system<Particle>()
            .kind(flecs::OnUpdate)
            .each([](flecs::iter &it, size_t, Particle &particle){
                auto dt = it.world().delta_time();

                // This is where we're integrating acceleration and velocity to get the new position
                particle.velocity += particle.acceleration * dt;
                particle.position += particle.velocity * dt;
            });

    world.system<Particle, const Camera>()
            .term_at(2).singleton()
            .kind(flecs::OnUpdate)
            .each([](Particle &particle, const Camera &camera){

            });

    world.system<const Particle, const Sprite, const Camera>()
            .term_at(3).singleton()
            .kind(flecs::OnStore)
            .each([&](const Particle &particle, const Sprite &sprite, const Camera &camera){
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(particle.position, 0.0f));
                transform = glm::scale(transform, glm::vec3(0.1f));
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
