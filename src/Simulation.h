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
        void computeDensityPressure();
        void computeForces(float deltaTime);
        float poly6();
        float spiky();
    private:
        std::vector<Model *> sceneModels;
        Renderer * sceneRenderer;
        InstancedRenderer * particlesRenderer;
        InstancedRenderer * gridRenderer;
        Grid * grid;
        Shader * sceneShader;
        Shader * particleShader;
        std::vector<Particle *> particles;
        std::size_t nbParticles;
        float particleRadius = 0.25f;

        float particleMass = 160.0f;
        float h, hs;
        const double pi = 3.14159265358979323846;
        const float G = -9.81f;
        const float restDensity = 1000.0f;
        glm::vec3 particleColor= glm::vec3(0.0,0.50f,1.0f);
        glm::vec3 boundaries = glm::vec3(15.0f,20.0f,15.0f);

        const float viscosity =10.0f;
};


#endif //COMP477PROJECT_SIMULATION_H
