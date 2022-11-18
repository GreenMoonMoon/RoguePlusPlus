#ifndef RPP_MODEL_H
#define RPP_MODEL_H

#include "textures.h"
#include "mesh.h"
#include "shader.h"

#include <memory>

struct Camera;

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

#endif // RPP_MODEL_H
