#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>


Texture::Texture(const TextureData &textureData) {
    unsigned char *data = stbi_load(textureData.path,
                                    &width,
                                    &height,
                                    &channelCount,
                                    0);
    if(data != nullptr){
        glGenTextures(1, &handle);
        glBindTexture(GL_TEXTURE_2D, handle);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

        switch(channelCount){
            case 3:
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                break;
            case 4:
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                break;
            default:
                glDeleteTextures(1, &handle);
                break;
        }

    } else {
        std::cerr << "Error could not open image: " << textureData.path << std::endl;
    }

    stbi_image_free(data);
    GenerateMipmap();
}

Texture::~Texture() {
    if(handle > 0) {
        glDeleteTextures(1, &handle);
    }
}

void Texture::GenerateMipmap() {
    glBindTexture(GL_TEXTURE_2D, handle);
    glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::Bind(int index) const {
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, handle);
}
