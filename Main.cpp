#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <iostream>

#include "Shader.hpp"
#include "Common.hpp"

#define WIDTH 1280
#define HEIGHT 720

const double cameraSpeed = 2.5f;
const double mouseSensitivity = 0.1f;

double deltaTime = 0.0f, lastFrame = 0.0f;
float fov = 45.0f;
double lastX = 0.0f, lastY = 0.0f;
double pitch = 0.0f, yaw = -90.0f;
glm::vec3 cameraPos   = glm::vec3(0, 0, 3);
glm::vec3 cameraFront = glm::vec3(0, 0, -1);
glm::vec3 cameraUp    = glm::vec3(0, 1, 0);

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

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    static bool firstMouse = true;
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    double xoffset = xpos - lastX;
    double yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f) pitch = 89.0f;
    else if (pitch < -89.0f) pitch = -89.0f;

    glm::vec3 direction = glm::vec3(
        cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
        sin(glm::radians(pitch)),
        sin(glm::radians(yaw)) * cos(glm::radians(pitch))
    );
    cameraFront = glm::normalize(direction);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    fov -= yoffset;
    if (fov > 45.0f) fov = 45.0f;
    else if (fov < 1.0f) fov = 1.0f;
}

void processInputs(GLFWwindow* window)
{
    float camSpeed = cameraSpeed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) cameraPos += camSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) cameraPos -= camSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * camSpeed;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * camSpeed;
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

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
    {
        std::cerr << "Failed to init GLAD\n";
        exit(EXIT_FAILURE);
    }

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetFramebufferSizeCallback(window, windowSetFramebufferCallback);
    glfwSetKeyCallback(window, windowKeyCallback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    CHKGL(glViewport(0, 0, WIDTH, HEIGHT));
    CHKGL(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
    CHKGL(glEnable(GL_DEPTH_TEST));

    const Shader shader{ "res/shaders/third.vert", "res/shaders/second.frag" };

    const float vertices[] = {
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

    glm::vec3 cubePositions[] = {
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

    const float radius = 10.0f;
    while (!glfwWindowShouldClose(window)) 
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInputs(window);

        CHKGL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        CHKGL(glActiveTexture(GL_TEXTURE0));
        CHKGL(glBindTexture(GL_TEXTURE_2D, texture1));
        CHKGL(glActiveTexture(GL_TEXTURE1));
        CHKGL(glBindTexture(GL_TEXTURE_2D, texture2));

        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        glm::mat4 projection = glm::perspective(glm::radians(fov), static_cast<float>(WIDTH) / static_cast<float>(HEIGHT), 0.1f, 100.0f);

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
