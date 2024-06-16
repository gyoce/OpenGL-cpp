#include "Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Common.hpp"

Texture::Texture(const std::string& path, GLenum format)
{
    createTexture();
    loadTexture(path, format);
}

void Texture::Use(const GLenum texture) const
{
    CHKGL(glActiveTexture(texture));
    CHKGL(glBindTexture(GL_TEXTURE_2D, id));
}

void Texture::createTexture()
{
    CHKGL(glGenTextures(1, &id));
    CHKGL(glBindTexture(GL_TEXTURE_2D, id));

    CHKGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    CHKGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

    CHKGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    CHKGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
}

void Texture::loadTexture(const std::string& path, GLenum format)
{
    int width, height, _;
    stbi_set_flip_vertically_on_load(true);

    unsigned char* data = stbi_load(path.c_str(), &width, &height, &_, 0);
    if (data == nullptr)
    {
        std::cerr << "Error while loading : " << path << "\n";
        exit(EXIT_FAILURE);
    }
    CHKGL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data));
    CHKGL(glGenerateMipmap(GL_TEXTURE_2D));
    stbi_image_free(data);
}
