#ifndef RPP_MESH_H
#define RPP_MESH_H

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

    static MeshData Quad;
};

struct Mesh {
    unsigned int vao = 0;
    unsigned int vbo = 0;
    unsigned int ebo = 0;
    unsigned int triangleCount = 0;
    unsigned int vertexCount = 0;

    explicit Mesh(const MeshData &meshData);
    ~Mesh();

    void Bind() const;
};

struct ParticleScope {};

struct Particle {
    vec2 position;
    vec2 velocity;
    vec2 acceleration;
    float mass;
 };

struct Sprite {
    unsigned int vao = 0;

    explicit Sprite();
    ~Sprite();

    void Bind() const;
};

#endif // RPP_MESH_H
