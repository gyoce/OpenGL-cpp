#ifndef COMMON_HPP
#define COMMON_HPP

#include "glad/glad.h"

#define CHKGL(op) do \
    { \
        op; \
        GLenum err = glGetError(); \
        if (err != GL_NO_ERROR) \
        { \
            std::cerr << "Failed to do \"" << #op << "\" : " << glGetErrorString(err) << " @ " << __FILE__ << ":" << __LINE__ << "\n"; \
            exit(EXIT_FAILURE); \
        } \
    } \
    while (0)

inline const char* glGetErrorString(const GLenum error)
{
    switch (error)
    {
        case GL_INVALID_ENUM: return "Invalid enum";
        case GL_INVALID_VALUE: return "Invalid value";
        case GL_INVALID_OPERATION: return "Invalid operation";
        case GL_STACK_OVERFLOW: return "Stack overflow";
        case GL_STACK_UNDERFLOW: return "Stack underflow";
        case GL_OUT_OF_MEMORY: return "Out of memory";
        case GL_INVALID_FRAMEBUFFER_OPERATION: return "Invalid framebuffer operation";
        default: return "Unknown";
    }
}

#endif // COMMON_HPP