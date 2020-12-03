//
// Created by Edouard on 2020-10-24.
//

#include "EventHandler.h"
float EventHandler::mouseX = SCR_WIDTH / 2.0;
float EventHandler::mouseY =  SCR_HEIGHT / 2.0;
bool EventHandler::firstMouse = true;
bool EventHandler::enableCursor = true;
bool EventHandler::fPress = false;
Camera * EventHandler::camera = nullptr;
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void EventHandler::init(GLFWwindow * window, Camera * cam) {
    camera = cam;
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}
void EventHandler::processInput(GLFWwindow *window, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS  && !enableCursor)
        camera->processKeyboard("FORWARD", deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S ) == GLFW_PRESS && !enableCursor)
        camera->processKeyboard("BACKWARD", deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A ) == GLFW_PRESS && !enableCursor)
        camera->processKeyboard("LEFT", deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D ) == GLFW_PRESS && !enableCursor)
        camera->processKeyboard("RIGHT", deltaTime);

    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS && !fPress) {
        fPress = true;
        if (enableCursor) {
            enableCursor = false;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        } else {
            enableCursor = true;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_RELEASE) {
        fPress = false;
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera->movementSpeed = 5.0f;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
        camera->movementSpeed = 2.5f;
}
void EventHandler::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera->processMouseScroll(yoffset);
}
void EventHandler::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
}
void EventHandler::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        mouseX = xpos;
        mouseY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - mouseX;
    float yoffset = mouseY - ypos; // reversed since y-coordinates go from bottom to top

    mouseX = xpos;
    mouseY = ypos;
    if (!enableCursor)
        camera->processMouseMovement(xoffset, yoffset);
}