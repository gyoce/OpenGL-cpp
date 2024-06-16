#include "Camera.hpp"

#include "glm/ext/matrix_transform.hpp"

Camera::Camera(const glm::vec3 startPos)
{
    position = startPos;
    worldUp = glm::vec3(0, 1, 0);
    updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix() const
{
    return glm::lookAt(position, position + front, up);
}

float Camera::GetZoom() const
{
    return zoom;
}

void Camera::ProcessKeyboard(const CameraMovement direction, const float deltaTime)
{
    const float velocity = movementSpeed * deltaTime;
    if (direction == CameraMovement::Forward)
        position += front * velocity;
    if (direction == CameraMovement::Backward)
        position -= front * velocity;
    if (direction == CameraMovement::Left)
        position -= right * velocity;
    if (direction == CameraMovement::Right)
        position += right * velocity;
}

void Camera::ProcessMouse(float xoffset, float yoffset)
{
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f) pitch = 89.0f;
    else if (pitch < -89.0f) pitch = -89.0f;

    updateCameraVectors();
}

void Camera::ProcessScroll(const float yoffset)
{
    zoom -= yoffset;
    if (zoom < 1.0f) zoom = 1.0f;
    else if (zoom > 45.0f) zoom = 45.0f;
}

void Camera::updateCameraVectors()
{
    front = glm::normalize(glm::vec3(
        cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
        sin(glm::radians(pitch)),
        sin(glm::radians(yaw)) * cos(glm::radians(pitch))
    ));
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}
