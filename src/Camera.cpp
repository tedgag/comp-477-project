//
// Created by Édouard Gagné on 2020-10-16.
//

#include "Camera.h"
Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) {
    this->position = position;
    this->worldUp = up;
    this->yaw = yaw;
    this->pitch = pitch;
    updateCameraVectors();
}

void Camera::setShaderUniforms(Shader * shader) {
    shader->use();
    glm::mat4 viewMatrix = glm::mat4(1.0f);
    viewMatrix = glm::lookAt(position, position + front,up);
    shader->setMat4("view", viewMatrix);
    glm::mat4 proj = glm::mat4(1.0f);
    proj = glm::perspective(zoomFactor, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.01f, 1000.0f);
    shader->setMat4("proj", proj);
    shader->setVec3("viewPos", position);


}

void Camera::updateCameraVectors() {
    // calculate the new Front vector
    glm::vec3 f;
    f.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    f.y = sin(glm::radians(pitch));
    f.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(f);
    // also re-calculate the Right and Up vector
    right = glm::normalize(glm::cross(front, worldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    up = glm::normalize(glm::cross(right, front));
}
// processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void Camera::processKeyboard(std::string direction, float deltaTime)
{
    float velocity = movementSpeed * deltaTime;
    if (direction == "FORWARD")
        position += front * velocity;
    if (direction == "BACKWARD")
        position -= front * velocity;
    if (direction == "LEFT")
        position -= right * velocity;
    if (direction == "RIGHT")
        position += right * velocity;
}

// processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void Camera::processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}

// processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
void Camera::processMouseScroll(float yoffset)
{
    zoomFactor -= (float)yoffset * mouseSensitivity;
    if (zoomFactor < 1.0f)
        zoomFactor = 1.0f;
    if (zoomFactor > 45.0f)
        zoomFactor = 45.0f;
}
