//
// Created by Édouard on 2020-12-02.
//

#ifndef COMP477PROJECT_USERINTERFACE_H
#define COMP477PROJECT_USERINTERFACE_H


#include "Simulation.h"

class UserInterface {
public:
    static void init(GLFWwindow *window, const char* glsl_version);
    static void render(Simulation * simulation);
private:
};


#endif //COMP477PROJECT_USERINTERFACE_H
