#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Shader.hpp"

#define WIDTH 1280
#define HEIGHT 720

void windowSetFramebufferCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void windowKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) 
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (key == GLFW_KEY_P && action == GLFW_PRESS)
    {
        static bool fill = true;
        if (fill) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        fill = !fill;
    }
}

int main(void) 
{
    if (!glfwInit()) 
    {
        std::cerr << "Failed to init glfw\n";
        exit(EXIT_FAILURE);
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL-C++", nullptr, nullptr);
    if (window == nullptr) 
    {
        std::cerr << "Failed to create GLFW Window\n";
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
    {
        std::cerr << "Failed to init GLAD\n";
        exit(EXIT_FAILURE);
    }

    glfwSetFramebufferSizeCallback(window, windowSetFramebufferCallback);
    glfwSetKeyCallback(window, windowKeyCallback);

    glViewport(0, 0, WIDTH, HEIGHT);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    Shader shader{ "res/shaders/first.vert", "res/shaders/first.frag" };

    while (!glfwWindowShouldClose(window)) 
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    exit(EXIT_SUCCESS);
}