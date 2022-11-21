#ifndef RPP_MESH_H
#define RPP_MESH_H

#include "glm/glm.hpp"

#include <vector>

struct VertexData {
    glm::vec2 position;
    glm::vec2 uv;
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

struct ParticleScope {
};

struct Particle {
    glm::vec2 position;
    glm::vec2 velocity;
    glm::vec2 acceleration;
    float radius = 1.0f;
    float mass = 1.0f;
};

struct Sprite {
    unsigned int vao = 0;

    explicit Sprite();

    ~Sprite();

    void Bind() const;
};

#endif // RPP_MESH_H
