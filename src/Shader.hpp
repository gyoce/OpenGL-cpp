#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>

#include "glad/glad.h"

class Shader 
{
public:
    Shader(const std::string& pathVertexShader, const std::string& pathFragmentShader);
    ~Shader();

private:
    static GLuint createShader(const std::string& shaderStr, GLenum shaderType);
    static GLuint createProgram(GLuint vs, GLuint fs);

    static void checkCompileStatus(GLuint shader, GLenum shaderType);
    static void checkLinkStatus(GLuint program);

    GLuint vs, fs;
    GLuint id;
};

#endif // SHADER_HPP