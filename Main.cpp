#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.hpp"
#include "Shader.hpp"
#include "Common.hpp"
#include "Texture.hpp"

void WindowSetFramebufferCallback(GLFWwindow* window, int width, int height);
void WindowKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void WindowCursorPosCallback(GLFWwindow* window, double xpos, double ypos);
void WindowScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void WindowProcessInputs(GLFWwindow* window);

constexpr int WIDTH = 1280;
constexpr int HEIGHT = 720;

Camera camera(glm::vec3(0, 0, 3));
float lastX = static_cast<float>(WIDTH) / 2;
float lastY = static_cast<float>(HEIGHT) / 2;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

void WindowSetFramebufferCallback(GLFWwindow* window, int width, int height)
{
    CHKGL(glViewport(0, 0, width, height));
}

void WindowKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) 
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

void WindowCursorPosCallback(GLFWwindow* window, double xposIn, double yposIn)
{
    const float xpos = static_cast<float>(xposIn);
    const float ypos = static_cast<float>(yposIn);

    static bool firstMouse = true;
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    const float xoffset = xpos - lastX;
    const float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouse(xoffset, yoffset);
}

void WindowScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessScroll(static_cast<float>(yoffset));
}

void WindowProcessInputs(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(CameraMovement::Forward, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(CameraMovement::Backward, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(CameraMovement::Left, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(CameraMovement::Right, deltaTime);
}

int main() 
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
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetFramebufferSizeCallback(window, WindowSetFramebufferCallback);
    glfwSetKeyCallback(window, WindowKeyCallback);
    glfwSetScrollCallback(window, WindowScrollCallback);
    glfwSetCursorPosCallback(window, WindowCursorPosCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
    {
        std::cerr << "Failed to init GLAD\n";
        exit(EXIT_FAILURE);
    }

    CHKGL(glViewport(0, 0, WIDTH, HEIGHT));
    CHKGL(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
    CHKGL(glEnable(GL_DEPTH_TEST));

    const Shader shader("res/shaders/third.vert", "res/shaders/second.frag");

    constexpr float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // A 
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // B
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // C
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // C
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // D
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // A

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // E
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // F
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // G
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // G
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // H
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // E

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    constexpr glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    GLuint VBO, VAO;
    CHKGL(glGenVertexArrays(1, &VAO));
    CHKGL(glGenBuffers(1, &VBO));

    CHKGL(glBindVertexArray(VAO));

    CHKGL(glBindBuffer(GL_ARRAY_BUFFER, VBO));
    CHKGL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

    CHKGL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0));
    CHKGL(glEnableVertexAttribArray(0));

    CHKGL(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))));
    CHKGL(glEnableVertexAttribArray(1));

    const Texture texture1("res/textures/container.jpg", GL_RGB);
    const Texture texture2("res/textures/awesomeface.png", GL_RGBA);

    shader.Use();
    shader.SetInt("texture1", 0);
    shader.SetInt("texture2", 1);

    while (!glfwWindowShouldClose(window)) 
    {
        const float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        WindowProcessInputs(window);

        CHKGL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        texture1.Use(GL_TEXTURE0);
        texture2.Use(GL_TEXTURE1);

        const glm::mat4 view = camera.GetViewMatrix();
        const glm::mat4 projection = glm::perspective(glm::radians(camera.GetZoom()), static_cast<float>(WIDTH) / static_cast<float>(HEIGHT), 0.1f, 100.0f);

        shader.Use();
        shader.SetMat4("projection", projection);
        shader.SetMat4("view", view);

        CHKGL(glBindVertexArray(VAO));
        for (int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * static_cast<float>(i);
            if (i % 3 == 0)
            {
                angle = static_cast<float>(glfwGetTime()) * 25.0f;
            }
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            shader.SetMat4("model", model);
            CHKGL(glDrawArrays(GL_TRIANGLES, 0, 36));
        }
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    CHKGL(glDeleteVertexArrays(1, &VAO));
    CHKGL(glDeleteBuffers(1, &VBO));

    glfwTerminate();
    exit(EXIT_SUCCESS);
}
