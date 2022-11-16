#ifndef SM64_TEXTURES_H
#define SM64_TEXTURES_H

#include "glad/gl.h"

/// Raw texture data
struct TextureData {
    const char *path = nullptr;
};

/// Gpu texture object
struct Texture {
    unsigned int handle = 0;
    int width;
    int height;
    int channelCount;

    Texture() = default;
    ~Texture();

    void Load(const TextureData &textureData);
    void GenerateMipmap();
    void Use(int index);
};

#endif // SM64_TEXTURES_H
