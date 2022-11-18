#include "model.h"
#include "camera.h"

void Model::Load(const ModelData &modelData) {
    texture.Load(modelData.textureData);
    texture.GenerateMipmap();

    mesh.Load(modelData.meshData);
    shader = Shader::Load(modelData.shaderData);
}

void Model::Draw(const Camera &camera, Renderer &renderer) {
    texture.Use(0);
    shader->Use();

    shader->SetMvpUniform(camera.view);
    renderer.RenderMesh(mesh);
}
