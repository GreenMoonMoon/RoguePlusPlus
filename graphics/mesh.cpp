#include "mesh.h"

Mesh::Mesh(const MeshData &meshData) {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 meshData.vertices.size() * sizeof(VertexData),
                 meshData.vertices.data(),
                 GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 meshData.indices.size() * sizeof(unsigned int),
                 meshData.indices.data(),
                 GL_STATIC_DRAW);
    triangleCount = meshData.indices.size();
    vertexCount = meshData.vertices.size();

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex
    // attributes(s).
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void *) 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void *) (2 * sizeof(float)));

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex
    // attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0 );

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS
    // stored in the VAO; keep the EBO bound.
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this
    // rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs)
    // when it's not directly necessary.
    // glBindVertexArray(0);
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
}

void Mesh::Bind() const {
    glBindVertexArray(vao);
}

MeshData MeshData::Quad{
        .vertices = {{vec2(-1.0f, -1.0f), vec2(0.0f, 0.0f)},
                     {vec2(1.0f, -1.0f),  vec2(1.0f, 0.0f)},
                     {vec2(1.0f, 1.0f),   vec2(1.0f, 1.0f)},
                     {vec2(-1.0f, 1.0f),  vec2(0.0f, 1.0f)}},
        .indices = {0, 3, 2, 0, 2, 1}
};
