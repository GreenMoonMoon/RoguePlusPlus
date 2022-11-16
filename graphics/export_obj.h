#ifndef SM64_EXPORT_OBJ_H
#define SM64_EXPORT_OBJ_H

#include "mesh.h"
#include "ObjWriter.h"

#include <fstream>
#include <stdio.h>


void writeMeshData(objwriter::ObjWriter &w, const char* meshName, const MeshData &meshData, int indexOffset = 0, bool writeNormal = false){
    w.objectName(meshName);
    for (const auto v : meshData.vertices) {
        w.vertex(v.position.x * 0.01f, v.position.y * 0.01f, v.position.z * 0.01f);
        w.texcoord(v.uv.x, v.uv.y);
        if(writeNormal) {
            w.normal(v.normal.x, v.normal.y, v.normal.z);
        }
    }
    for (int i = 0; i < meshData.indices.size(); i += 3) {
        int t1 = meshData.indices[i] + 1 + indexOffset;
        int t2 = meshData.indices[i + 1] + 1 + indexOffset;
        int t3 = meshData.indices[i + 2] + 1 + indexOffset;
        if(writeNormal){
            w.face_vtn(t1, t1, t1, t2, t2, t2, t3, t3, t3);
        } else {
            w.face_vt(t1, t1, t2, t2, t3, t3);
        }
    }
}

void ExportMeshDataObjFile(MeshData meshData, const char* name) {
    std::fstream file;
    file.open(name, std::ios::out);
    objwriter::ObjWriter w(file);
    writeMeshData(w, "mesh_data", meshData, 0);
    file.close();
}

void ExportMeshDataObjFile(std::vector<MeshData> meshesData, const char* name) {
    std::fstream file;
    file.open(name, std::ios::out);
    objwriter::ObjWriter w(file);
    int ni = 1;
    char objName[200];
    int indexOffset = 0;
    for (auto meshData : meshesData) {
        sprintf_s(objName, "mesh_%d", ni++);
        writeMeshData(w, objName, meshData, indexOffset);
        indexOffset += meshData.vertices.size();
    }
    file.close();
}

#endif // SM64_EXPORT_OBJ_H
