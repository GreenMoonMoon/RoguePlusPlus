#include "mesh.h"

void Mesh::Load(const MeshData &meshData) {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 meshData.vertices.size() * sizeof(Vertex),
                 meshData.vertices.data(),
                 GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 meshData.indices.size() * sizeof(unsigned int),
                 meshData.indices.data(),
                 GL_STATIC_DRAW);
    triangleCount = meshData.indices.size();

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex
    // attributes(s).
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) (3 * sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) (6 * sizeof(float)));
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) (8 * sizeof(float)));

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex
    // attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

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

const float cr = 1.0f/255.0f;
const float uvr = 1.0f/1008.0f;

Vertex VertexFromVtxNormal(const Vtx &vtx) {
    Vertex v;
    v.position = vec3( (float) vtx.n.ob[0], (float) vtx.n.ob[1], (float) vtx.n.ob[2] );
    v.uv = vec2((float) vtx.n.tc[0], (float) vtx.n.tc[1]);
    v.normal = vec3((float)vtx.n.n[0], (float) vtx.n.n[1], (float) vtx.n.n[2]);
    v.color = vec4(0.0f, 0.0f, 0.0f, (float)vtx.n.a * cr);

    // Scale down
    v.position *= 0.01f;
    v.uv *= uvr;

    return v;
}

Vertex VertexFromVtxColor(const Vtx &vtx) {
    Vertex v;
    v.position = vec3( (float) vtx.v.ob[0], (float) vtx.v.ob[1], (float) vtx.v.ob[2] );
    v.uv = vec2((float) vtx.v.tc[0], (float) vtx.v.tc[1]);
    v.normal = vec3(0.0f);
    v.color = vec4((float)vtx.v.cn[0] * cr,
                   (float)vtx.v.cn[1] * cr,
                   (float)vtx.v.cn[2] * cr,
                   (float)vtx.v.cn[3] * cr);

    // Scale down
    v.position *= 0.005f; // Using the BreakableBox as a measurement unit it should be 1m x 1m x 1m.
    v.uv *= uvr;

    return v;
}

void MeshData::AddVertices(const Vtx *vtx, int vtxCount, int) {
    indexOffset = vertices.size();
    for(int i = 0; i < vtxCount; i++){
        vertices.push_back(VertexFromVtxColor(vtx[i]));
    }
}

void MeshData::AddTriangles(int a1, int a2, int a3, int, int b1, int b2, int b3, int) {
    indices.push_back(a1 + indexOffset);
    indices.push_back(a2 + indexOffset);
    indices.push_back(a3 + indexOffset);
    indices.push_back(b1 + indexOffset);
    indices.push_back(b2 + indexOffset);
    indices.push_back(b3 + indexOffset);
}

void MeshData::AddTriangles(int a1, int a2, int a3, int) {
    indices.push_back(a1 + indexOffset);
    indices.push_back(a2 + indexOffset);
    indices.push_back(a3 + indexOffset);
}
