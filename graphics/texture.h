#ifndef RPP_TEXTURE_H
#define RPP_TEXTURE_H

#include "glad/gl.h"

/// Raw texture data
struct TextureData {
    const char *path = nullptr;
};

/// Gpu texture object
struct Texture {
    unsigned int handle = 0;
    int width = 0;
    int height = 0;
    int channelCount = 0;

    explicit Texture(const TextureData &textureData);
    ~Texture();

    void GenerateMipmap();
    void Bind(int index) const;
};

#endif // RPP_TEXTURE_H
