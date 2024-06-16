#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>

constexpr float YAW         = -90.0f;
constexpr float PITCH       =   0.0f;
constexpr float SPEED       =   2.5f;
constexpr float SENSITIVITY =   0.1f;
constexpr float ZOOM        =  45.0f;

enum class CameraMovement
{
    Forward,
    Backward,
    Right,
    Left
};

class Camera
{
public:
    Camera(glm::vec3 startPos);

    void ProcessKeyboard(CameraMovement direction, float deltaTime);
    void ProcessMouse(float xoffset, float yoffset);
    void ProcessScroll(float yoffset);
    glm::mat4 GetViewMatrix() const;
    float GetZoom() const;

private:
    void updateCameraVectors();

    glm::vec3 position, front, up, right, worldUp;
    float yaw = YAW, pitch = PITCH;
    float movementSpeed = SPEED, mouseSensitivity = SENSITIVITY, zoom = ZOOM;
};

#endif // CAMERA_HPP