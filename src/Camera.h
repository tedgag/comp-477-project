//
// Created by Édouard Gagné on 2020-10-16.
//

#ifndef COMP477PROJECT_CAMERA_H
#define COMP477PROJECT_CAMERA_H
#include "helpers/IncludeHeader.h"

#include <string>
#include <vector>

#include "Shader.h"

class Camera {
public:
    // camera Attributes
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;
    // euler Angles
    float yaw;
    float pitch;
    // camera options
    float movementSpeed = 2.5f;
    float mouseSensitivity = 0.1f;
    float zoomFactor = 45.0f;

    Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch);
    void processKeyboard(std::string, float deltaTime);
    void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
    void processMouseScroll(float yoffset);
    void setViewMatrix(Shader * shader);
private:
    void updateCameraVectors();
};


#endif //COMP477PROJECT_CAMERA_H
