#ifndef SM64_MESH_H
#define SM64_MESH_H

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

// N64 Data format
struct Vtx_t {
#ifndef GBI_FLOATS
    short		ob[3];	/* x, y, z */
#else
    float		ob[3];	/* x, y, z */
#endif
    unsigned short	flag;
    short		tc[2];	/* texture coord */
    unsigned char	cn[4];	/* color & alpha */
} ;
// N64 Data format
struct Vtx_tn {
#ifndef GBI_FLOATS
    short		ob[3];	/* x, y, z */
#else
    float		ob[3];	/* x, y, z */
#endif
    unsigned short	flag;
    short		tc[2];	/* texture coord */
    signed char	n[3];	/* normal */
    unsigned char   a;      /* alpha  */
};
// N64 Data format
union Vtx {
    Vtx_t		v;  /* Use this one for colors  */
    Vtx_tn              n;  /* Use this one for normals */
    long long int	force_structure_alignment;
};


struct Vertex {
    vec3 position;
    vec3 normal;
    vec2 uv;
    vec4 color;
};

struct MeshData {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    int indexOffset = 0;

    void AddVertices(const Vtx vtx[], int vtxCount, int);
    void AddTriangles(int a1, int a2, int a3, int, int b1, int b2, int b3, int);
    void AddTriangles(int a1, int a2, int a3, int);
};

struct Mesh {
    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;
    unsigned int triangleCount;

    ~Mesh();

    void Load(const MeshData &meshData);
};

Vertex VertexFromVtxColor(const Vtx &vtx) ;

Vertex VertexFromVtxNormal(const Vtx &vtx);

#endif // SM64_MESH_H
