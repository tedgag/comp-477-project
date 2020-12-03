//
// Created by Édouard on 2020-12-02.
//

#ifndef COMP477PROJECT_SKYRENDERER_H
#define COMP477PROJECT_SKYRENDERER_H


#include "Model.h"
#include "Camera.h"

class SkyRenderer {
public:
    SkyRenderer(Shader* shader, Camera* camera, std::vector<std::string> faces);
    void setup();
    void render();
private :
    Shader* shader;
    Camera * camera;
    Model * model;
    std::vector<std::string> faces;
};


#endif //COMP477PROJECT_SKYRENDERER_H
