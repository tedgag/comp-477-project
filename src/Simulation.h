//
// Created by Édouard Gagné on 2020-10-16.
//

#ifndef COMP477PROJECT_SIMULATION_H
#define COMP477PROJECT_SIMULATION_H

#include "Renderer.h"
#include "InstancedRenderer.h"
struct Particle {
    glm::vec3 position;
};
class Simulation {
    public:
        Simulation(Camera * camera);
        void run();
    private:
        std::vector<Model *> sceneModels;
        std::vector<Particle> particles;
        Renderer * sceneRenderer;
        InstancedRenderer * particlesRenderer;
        Model * particleModel;
};


#endif //COMP477PROJECT_SIMULATION_H
