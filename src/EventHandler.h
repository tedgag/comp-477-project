//
// Created by Edouard on 2020-10-24.
//

#ifndef COMP477PROJECT_EVENTHANDLER_H
#define COMP477PROJECT_EVENTHANDLER_H
#include "helpers/IncludeHeader.h"
#include "Camera.h"
#include "Scene.h"
#include <memory>
class EventHandler {
private:
    static float mouseX;
    static float mouseY;
    static bool firstMouse;
    static bool enableCursor;
    static bool fPress;
public:
    static std::shared_ptr<Camera> camera;
    static std::shared_ptr<Scene> scene;
    static void init(GLFWwindow* window, std::shared_ptr<Camera> camera, std::shared_ptr<Scene> scene);
    static void processInput(GLFWwindow *window, float deltaTime);
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
};


#endif //COMP477PROJECT_EVENTHANDLER_H
