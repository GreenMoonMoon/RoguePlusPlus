#ifndef SM64_MODEL_H
#define SM64_MODEL_H

#include "textures.h"
#include "mesh.h"
#include "shader.h"

#include <memory>

/// ModelData only represent raw object data that can be loaded at runtime.
struct ModelData {
    TextureData textureData;
    MeshData meshData;
    ShaderData shaderData;
};

struct Model{
    Mesh mesh;
    Texture texture;
    std::shared_ptr<Shader> shader;

    ~Model() = default;

    void Load(const ModelData &modelData);
    void Draw(const Camera &camera, Renderer &renderer);
};

#endif // SM64_MODEL_H
