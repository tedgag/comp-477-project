//
// Created by Édouard Gagné on 2020-10-16.
//

#ifndef COMP477PROJECT_SIMULATION_H
#define COMP477PROJECT_SIMULATION_H

#include "Renderer.h"
#include "InstancedRenderer.h"
#include "Grid.h"
class Simulation {
    public:
        Simulation(Camera * camera);
        void run();
    private:
        std::vector<Model *> sceneModels;
        Renderer * sceneRenderer;
        InstancedRenderer * particlesRenderer;
        Grid * grid;
        Shader * sceneShader;
        Shader * particleShader;
        std::vector<glm::vec3> positions;
        std::vector<glm::vec3> cellPositions;
        std::vector<std::vector<glm::vec3>> neighbors;
        std::size_t nbParticles;
        float particleRadius = 0.25f;
        glm::vec3 particleColor= glm::vec3(0.5f,0.5f,0.5f);
        glm::vec3 boxDimensions = glm::vec3(15.0f,20.0f,15.0f);
};


#endif //COMP477PROJECT_SIMULATION_H
