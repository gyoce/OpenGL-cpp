#include "Shader.hpp"

#include <iostream>

#include "Utils.hpp"

constexpr int SIZE_INFO_LOG = 1024;

Shader::Shader(const std::string& pathVertexShader, const std::string& pathFragmentShader)
{
    const std::string vertexShader = Utils::GetFileContent(pathVertexShader);
    const std::string fragmentShader = Utils::GetFileContent(pathFragmentShader);
    vs = createShader(vertexShader, GL_VERTEX_SHADER);
    fs = createShader(fragmentShader, GL_FRAGMENT_SHADER);
    id = createProgram(vs, fs);
}

Shader::~Shader()
{
    glDeleteShader(vs);
    glDeleteShader(fs);
    glDeleteProgram(id);
}

GLuint Shader::createShader(const std::string& shaderStr, const GLenum shaderType)
{
    const char* shaderChar = shaderStr.c_str();
    const GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderChar, nullptr);
    glCompileShader(shader);
    checkCompileStatus(shader, shaderType);
    return shader;
}

GLuint Shader::createProgram(const GLuint vs, const GLuint fs)
{
    const GLuint program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    checkLinkStatus(program);
    return program;
}

void Shader::checkCompileStatus(const GLuint shader, const GLenum shaderType)
{
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success) return;

    char infoLog[SIZE_INFO_LOG];
    glGetShaderInfoLog(shader, SIZE_INFO_LOG, nullptr, infoLog);
    const char* shaderTypeStr = shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment";
    std::cerr << "Failed to compile " << shaderTypeStr << " shader : " << infoLog << "\n";
    exit(EXIT_FAILURE);
}

void Shader::checkLinkStatus(const GLuint program)
{
    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (success) return;

    char infoLog[SIZE_INFO_LOG];
    glGetProgramInfoLog(program, SIZE_INFO_LOG, nullptr, infoLog);
    std::cerr << "Failed to link program : " << infoLog << "\n";
    exit(EXIT_FAILURE);
}