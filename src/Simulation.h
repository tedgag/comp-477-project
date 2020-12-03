//
// Created by Édouard Gagné on 2020-10-16.
//

#ifndef COMP477PROJECT_SIMULATION_H
#define COMP477PROJECT_SIMULATION_H

#include "Renderer.h"
#include "InstancedRenderer.h"
#include "SkyRenderer.h"
#include "Grid.h"
class Simulation {
    public:
        Simulation(Camera * camera);
        void run();
        void setBoundaries(glm::vec3 dimensions);
        void setFluid();
        void setFluid(glm::vec3 position, glm::vec3 dimensions);
        bool play = true;
        bool start = false;
        std::vector<Particle *> particles;
        int nbParticles;
        int maxParticles = 10000;
        float particleRadius = 0.2f;
        glm::vec3 fluidPosition;
        glm::vec3 fluidDimensions;
        float particleMass = 80.0f;
        float h, hs;
        glm::vec3 particleColor= glm::vec3(0.0,0.50f,1.0f);
        glm::vec3 gridBoundaries = glm::vec3(15.0f,20.0f,15.0f);
        glm::vec3 gridDimensions;
        const float viscosity =10.0f;
    private:
        Model * particleModel;
        Model * boxModel;
        Model * skyBoxModel;
        std::vector<Model *> sceneModels;
        Renderer * sceneRenderer;
        InstancedRenderer * particlesRenderer;
        InstancedRenderer * gridRenderer;
        SkyRenderer * skyRenderer;
        Grid * grid;
        Shader * sceneShader;
        Shader * particleShader;
        Shader * skyShader;
        const double pi = 3.14159265358979323846;
        const float G = -9.81f;
        const float restDensity = 1000.0f;
        void timeIntegration( float deltaTime);
        void computeDensityPressure();
        void computeForces();
        float poly6();
        float spiky();

};


#endif //COMP477PROJECT_SIMULATION_H
