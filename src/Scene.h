//
// Created by Édouard on 2020-12-03.
//

#ifndef COMP477PROJECT_SCENE_H
#define COMP477PROJECT_SCENE_H

#include "Model.h"
#include "Camera.h"
#include "Simulation.h"
class Scene {
public:
    void render();
    void init();
    GLuint setupInstancedBuffer(Model * model);
    void setupSkybox( std::vector<std::string> faces);
    glm::vec3 particleColor= glm::vec3(0.0,0.50f,1.0f);
    bool play = true;
    bool start = false;
private:
    Camera * camera;
    Simulation * simulation;
    Model * particleModel;
    Model * boxModel;
    Model * skyBoxModel;
    std::vector<Model *> sceneModels;
    Shader * sceneShader;
    Shader * particleShader;
    Shader * skyShader;
    GLuint particlesBuffer;

};


#endif //COMP477PROJECT_SCENE_H
