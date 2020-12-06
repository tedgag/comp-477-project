//
// Created by Édouard Gagné on 2020-10-16.
//

#ifndef COMP477PROJECT_SIMULATION_H
#define COMP477PROJECT_SIMULATION_H
#include "Grid.h"
class Simulation {
    public:
        Simulation(float particleRadius);

        void run(float deltaTime);
        std::vector<Particle * > particles;


        Grid * grid;
        float particleMass;
        float h, hs;
        float particleRadius;
        glm::vec3 gravity;
        float viscosity;
    private:
        const double pi = 3.14159265358979323846;
        const float restDensity = 1000.0f;
        void timeIntegration( float deltaTime);
        void computeDensityPressure();
        void computeForces();
        float poly6();
        float spiky();

};


#endif //COMP477PROJECT_SIMULATION_H
