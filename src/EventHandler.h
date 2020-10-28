//
// Created by Edouard on 2020-10-24.
//

#ifndef COMP477PROJECT_EVENTHANDLER_H
#define COMP477PROJECT_EVENTHANDLER_H
#include "helpers/IncludeHeader.h"
#include "Camera.h"
class EventHandler {
private:
    static float mouseX;
    static float mouseY;
    static bool firstMouse;
public:
    static Camera * camera;
    static void init(GLFWwindow* window, Camera * camera);
    static void processInput(GLFWwindow *window, float deltaTime);
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
};


#endif //COMP477PROJECT_EVENTHANDLER_H
