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
        void timeIntegration( float deltaTime);
        void computeForces();
        void collisionHandling();
    private:
        std::vector<Model *> sceneModels;
        Renderer * sceneRenderer;
        InstancedRenderer * particlesRenderer;
        Grid * grid;
        Shader * sceneShader;
        Shader * particleShader;
        std::vector<glm::vec3> positions;
        std::vector<glm::vec3> velocities;
        std::vector<glm::vec3> accelerations;
        std::vector<std::vector<int>> neighbors;
        std::size_t nbParticles;
        float particleRadius = 0.25f;
        float particleMass = 0.25f;
        const float g = -9.81f;
        glm::vec3 particleColor= glm::vec3(0.5f,0.5f,0.5f);
        glm::vec3 boundaries = glm::vec3(15.0f,20.0f,15.0f);
        const float boundDamping = -0.5f;
        const float displacement = 0.25f;
};


#endif //COMP477PROJECT_SIMULATION_H
