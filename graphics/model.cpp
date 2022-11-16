#include "model.h"

void Model::Load(const ModelData &modelData) {
    texture.Load(modelData.textureData);
    texture.GenerateMipmap();

    mesh.Load(modelData.meshData);
    shader = Shader::Load(modelData.shaderData);
}

void Model::Draw(const Camera &camera, Renderer &renderer) {
    texture.Use(0);

    shader->Use();
    auto mvp = camera.projection * camera.transform;
    shader->SetMvpUniform(mvp);

    renderer.RenderMesh(mesh);
}
