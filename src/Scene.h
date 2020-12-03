//
// Created by Édouard on 2020-12-03.
//

#ifndef COMP477PROJECT_SCENE_H
#define COMP477PROJECT_SCENE_H

#include "Renderer.h"
#include "Camera.h"
#include "Simulation.h"
class Scene {
public:
    Scene(Camera * camera);
    void render();
    void setBoundaries(glm::vec3 newDimensions);
    void setFluid(glm::vec3 newPosition, glm::vec3 newDimensions);
    void setFluid();
    glm::vec3 particleColor= glm::vec3(0.0,0.50f,1.0f);
    float particleRadius = 0.2f;
    int maxParticles = 10000;
    int nbParticles;
    bool play = true;
    bool start = false;
    glm::vec3 gridBoundaries = glm::vec3(15.0f,20.0f,15.0f);
    glm::vec3 gridDimensions;
    glm::vec3 fluidPosition;
    glm::vec3 fluidDimensions;
private:
    Camera * camera;
    Simulation * simulation;
    Renderer * renderer;
};


#endif //COMP477PROJECT_SCENE_H
