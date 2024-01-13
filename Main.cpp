#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <iostream>

#include "Shader.hpp"
#include "Common.hpp"
#include "Maths.hpp"

#define WIDTH 1280
#define HEIGHT 720

void windowSetFramebufferCallback(GLFWwindow* window, int width, int height)
{
    CHKGL(glViewport(0, 0, width, height));
}

void windowKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) 
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (key == GLFW_KEY_P && action == GLFW_PRESS)
    {
        static bool fill = true;
        if (fill) CHKGL(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
        else CHKGL(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
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

    CHKGL(glViewport(0, 0, WIDTH, HEIGHT));
    CHKGL(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));

    const Shader shader{ "res/shaders/second.vert", "res/shaders/second.frag" };

    const float vertices[] = {
        // positions          // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
    };

    const unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    GLuint VBO, VAO, EBO;
    CHKGL(glGenVertexArrays(1, &VAO));
    CHKGL(glGenBuffers(1, &VBO));
    CHKGL(glGenBuffers(1, &EBO));

    CHKGL(glBindVertexArray(VAO));

    CHKGL(glBindBuffer(GL_ARRAY_BUFFER, VBO));
    CHKGL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

    CHKGL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
    CHKGL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

    CHKGL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0));
    CHKGL(glEnableVertexAttribArray(0));

    CHKGL(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))));
    CHKGL(glEnableVertexAttribArray(1));

    GLuint texture1, texture2;

    CHKGL(glGenTextures(1, &texture1));
    CHKGL(glBindTexture(GL_TEXTURE_2D, texture1));

    CHKGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    CHKGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

    CHKGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    CHKGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);

    const char* containerPath = "res/textures/container.jpg";
    unsigned char* data = stbi_load(containerPath, &width, &height, &nrChannels, 0);
    if (data == nullptr)
    {
        std::cerr << "Error while loading : " << containerPath << "\n";
        exit(EXIT_FAILURE);
    }
    CHKGL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data));
    CHKGL(glGenerateMipmap(GL_TEXTURE_2D));
    stbi_image_free(data);

    CHKGL(glGenTextures(1, &texture2));
    CHKGL(glBindTexture(GL_TEXTURE_2D, texture2));

    CHKGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    CHKGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

    CHKGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    CHKGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    const char* awesomeFacePath = "res/textures/awesomeface.png";
    data = stbi_load(awesomeFacePath, &width, &height, &nrChannels, 0);
    if (data == nullptr)
    {
        std::cerr << "Error while loading : " << awesomeFacePath << "\n";
        exit(EXIT_FAILURE);
    }
    CHKGL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
    CHKGL(glGenerateMipmap(GL_TEXTURE_2D));
    stbi_image_free(data);

    shader.Use();
    shader.SetInt("texture1", 0);
    shader.SetInt("texture2", 1);

    GLuint transformLoc;
    CHKGL(transformLoc = glGetUniformLocation(shader.Id, "transform"));

    while (!glfwWindowShouldClose(window)) 
    {
        CHKGL(glClear(GL_COLOR_BUFFER_BIT));

        CHKGL(glActiveTexture(GL_TEXTURE0));
        CHKGL(glBindTexture(GL_TEXTURE_2D, texture1));
        CHKGL(glActiveTexture(GL_TEXTURE1));
        CHKGL(glBindTexture(GL_TEXTURE_2D, texture2));

        Mat4 transform = Mat4{ 1.0f };
        transform = transform.Translate(Vec3{ 0.5f, -0.5f, 0.0f });
        transform = transform.Rotate(static_cast<float>(glfwGetTime()), Vec3{ 0.0f, 0.0f, 1.0f });

        shader.Use();
        CHKGL(glUniformMatrix4fv(transformLoc, 1, GL_FALSE, transform.ValuePtr()));

        CHKGL(glBindVertexArray(VAO));
        CHKGL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    CHKGL(glDeleteVertexArrays(1, &VAO));
    CHKGL(glDeleteBuffers(1, &VBO));
    CHKGL(glDeleteBuffers(1, &EBO));

    glfwTerminate();
    exit(EXIT_SUCCESS);
}