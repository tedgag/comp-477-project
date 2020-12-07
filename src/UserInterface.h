//
// Created by Édouard on 2020-12-02.
//

#ifndef COMP477PROJECT_USERINTERFACE_H
#define COMP477PROJECT_USERINTERFACE_H


#include "Scene.h"
class UserInterface {
public:
    static void init(GLFWwindow *window, const char* glsl_version);
    static void render(const std::shared_ptr<Scene>&scene, float deltaTime);
};


#endif //COMP477PROJECT_USERINTERFACE_H
