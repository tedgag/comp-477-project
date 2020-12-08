//
// Created by Édouard on 2020-12-03.
//

#ifndef COMP477PROJECT_SCENE_H
#define COMP477PROJECT_SCENE_H

#include "Renderer.h"
#include "Camera.h"
#include "Simulation.h"
struct Params {
    glm::vec3 boundaries;
    glm::vec3 gravity;
    glm::vec3 particleColor;
    float viscosity;
};
class Scene {
public:
    explicit Scene(const std::shared_ptr<Camera>& camera);
    void render(float deltaTime);
    void reset ();
    void save();
    void setBoundaries(glm::vec3 newDimensions);
    void setFluid(glm::vec3 newPosition, glm::vec3 newDimensions);
    void setFluid();
    void setGravity(glm::vec3 gravity);
    void setViscosity(float viscosity);
    void setColor(glm::vec3 color);
    void setMass(float particleMass);
    void setSkybox(bool enabled);
    void setBounds(bool enabled);
    glm::vec3 particleColor= glm::vec3(0.0,0.50f,1.0f);
    float particleRadius = 0.2f;
    float particleMass = 100.0f;
    int maxParticles = 100000;
    int nbParticles = 0;
    bool enableSkybox;
    bool enableBounds;
    bool showMenu = true;
    bool play = false;
    bool start = false;
    glm::vec3 boundaries = glm::vec3(15.0f,20.0f,15.0f) ;
    glm::vec3 fluidPosition;
    glm::vec3 fluidDimensions;
    glm::vec3 gravity = glm::vec3(0.0f, -9.81f, 0.0f);
    float viscosity = 20.0f;
    Params savedParams;
    std::shared_ptr<Simulation> simulation;
private:
    std::shared_ptr<Renderer> renderer;
};


#endif //COMP477PROJECT_SCENE_H
