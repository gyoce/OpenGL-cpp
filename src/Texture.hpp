#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>

#include <glad/glad.h>

class Texture
{
public:
    explicit Texture(const std::string& path, GLenum format);
    void Use(GLenum texture) const;

private:
    void createTexture();
    static void loadTexture(const std::string& path, GLenum format);

    GLuint id;
};

#endif // TEXTURE_HPP