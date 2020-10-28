//
// Created by Edouard on 2020-10-27.
//

#ifndef COMP477PROJECT_INSTANCEDRENDERER_H
#define COMP477PROJECT_INSTANCEDRENDERER_H

#include "Model.h"
#include "Shader.h"
#include "Camera.h"

class InstancedRenderer {
public:

    InstancedRenderer(Shader * shader, Camera * camera, Model * model);

    void render(std::vector<glm::mat4> instances);
private:
    Shader* shader;
    Camera * camera;
    Model* model;
    GLuint modelsBuffer;
    void setup();
};


#endif //COMP477PROJECT_INSTANCEDRENDERER_H