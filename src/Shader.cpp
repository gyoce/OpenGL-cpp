#include "Shader.hpp"

#include <iostream>

#include "Utils.hpp"
#include "Common.hpp"

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
    CHKGL(glDeleteShader(vs));
    CHKGL(glDeleteShader(fs));
    CHKGL(glDeleteProgram(id));
}

GLuint Shader::createShader(const std::string& shaderStr, const GLenum shaderType)
{
    const char* shaderChar = shaderStr.c_str();
    GLuint shader;
    CHKGL(shader = glCreateShader(shaderType));
    CHKGL(glShaderSource(shader, 1, &shaderChar, nullptr));
    CHKGL(glCompileShader(shader));
    checkCompileStatus(shader, shaderType);
    return shader;
}

GLuint Shader::createProgram(const GLuint vs, const GLuint fs)
{
    GLuint program;
    CHKGL(program = glCreateProgram());
    CHKGL(glAttachShader(program, vs));
    CHKGL(glAttachShader(program, fs));
    CHKGL(glLinkProgram(program));
    checkLinkStatus(program);
    return program;
}

void Shader::checkCompileStatus(const GLuint shader, const GLenum shaderType)
{
    GLint success;
    CHKGL(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));
    if (success) return;

    char infoLog[SIZE_INFO_LOG];
    CHKGL(glGetShaderInfoLog(shader, SIZE_INFO_LOG, nullptr, infoLog));
    const char* shaderTypeStr = shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment";
    std::cerr << "Failed to compile " << shaderTypeStr << " shader : " << infoLog << "\n";
    exit(EXIT_FAILURE);
}

void Shader::checkLinkStatus(const GLuint program)
{
    GLint success;
    CHKGL(glGetProgramiv(program, GL_LINK_STATUS, &success));
    if (success) return;

    char infoLog[SIZE_INFO_LOG];
    CHKGL(glGetProgramInfoLog(program, SIZE_INFO_LOG, nullptr, infoLog));
    std::cerr << "Failed to link program : " << infoLog << "\n";
    exit(EXIT_FAILURE);
}