#ifndef RPP_MESH_H
#define RPP_MESH_H

#include "shader.h"
#include "textures.h"
#include "renderer.h"
#include "camera.h"
#include "glad/gl.h"
#include "glm/glm.hpp"

#include <vector>

using glm::mat4x4;
using glm::vec2;
using glm::vec3;
using glm::vec4;

struct VertexData {
    vec2 position;
    vec2 uv;
};

struct MeshData {
    std::vector<VertexData> vertices;
    std::vector<unsigned int> indices;
};

struct Mesh {
    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;
    unsigned int triangleCount;

    ~Mesh();

    void Load(const MeshData &meshData);
};

/// Generic quad geometry
/// TODO: move to the cpp file and add a function to quickly load it based on some parameters
const MeshData Quad{
        .vertices = {{vec2(-1.0f, -1.0f), vec2(0.0f, 0.0f)},
                     {vec2(1.0f, -1.0f),  vec2(1.0f, 0.0f)},
                     {vec2(1.0f, 1.0f),   vec2(1.0f, 1.0f)},
                     {vec2(-1.0f, 1.0f),  vec2(0.0f, 1.0f)}},
        .indices = {0, 3, 2, 0, 2, 1}
};

#endif // RPP_MESH_H
