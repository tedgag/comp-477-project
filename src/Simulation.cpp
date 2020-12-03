//
// Created by Édouard Gagné on 2020-10-16.
//

#include <iostream>
#include "Simulation.h"
#include <cmath>

Simulation::Simulation(float particleRadius) {
    this->particleRadius = particleRadius;
    h = 4*particleRadius;
    hs = h * h;
    grid = new Grid( h, particleRadius);
}

void Simulation::run() {
    grid->findNeighbors(particles, h);
    computeDensityPressure();
    float deltaTime = 0.05f * particleRadius;
    computeForces();
    timeIntegration(deltaTime);
    grid->collisionHandling(particles);
}
void Simulation::computeDensityPressure() {
    #pragma omp parallel for
    for (int i =0 ; i<particles.size(); i++) {
        Particle * p = particles[i];
        p->density = poly6()*pow(hs, 3.0f);
        for(int j =0 ; j<p->neighbors.size(); j++)
        {
            auto n = p->neighbors[j];
            auto r = p->position - n->position;
            float r2 = glm::length(r) * glm::length(r);

            if(r2 < hs)
            {
                // this computation is symmetric
                p->density += poly6()*pow(hs-r2, 3.0f);
            }
        }


        p->density *= particleMass;

        // Pressure using the Tait equation
        float ratio = p->density/restDensity;
        if(ratio < 1.0f) {
            p->pressure = 0.0f;
        } else {
            p->pressure = pow(ratio, 7.0f) -1.0f;
        }

        /*
        p->pressure = 200.0f * ( p->density-restDensity);
        */
    }
}
void Simulation::computeForces() {
    #pragma omp parallel for
    for (int i =0 ; i<particles.size(); i++) {
        glm::vec3 accel = glm::vec3(0.0f,0.0f,0.0f);

        Particle * p = particles[i];

        float kp = p->pressure / (p->density * p->density);
        for (int j =0 ; j<p->neighbors.size(); j++) {
            Particle * n = p->neighbors[j];
            float r = glm::length(p->position - n->position);
            float r2 = r * r;
            if (r2 <= hs && r2 > 0) {
                // Pressure forces
                float kn = n->pressure / (n->density * n->density);
                float k = (kp + kn);
                // momentum equation
                accel -= glm::normalize(p->position - n->position)* k * spiky()*(float)pow(hs-r2,2.0f);

                // Viscosity
                accel += viscosity*(n->velocity - p->velocity)/n->density * poly6()*(float)pow(hs-r2, 3.0f);
            }

        }

        for(int j = 0; j< p->ghosts.size(); j++) {

            auto gDist = p->ghosts[j];
            auto r = glm::length(gDist);
            float r2 = r * r;
            if (r2 <= hs && r2 > 0) {
                accel -= glm::normalize(gDist) * kp*spiky()*(float)pow(hs-r2,2.0f);
            }
        }

        // Gravity
        accel *= particleMass;
        accel .y += G;
        p->acceleration = accel;

    }

}
void Simulation::timeIntegration( float deltaTime) {
    #pragma omp parallel for
    for (int i =0 ; i<particles.size(); i++) {
        auto * p = particles[i];
        p->velocity += p->acceleration * deltaTime;
        glm::vec3 avgVelocity = p->velocity;
        /*
        for (int j =0 ; j<p->neighbors.size(); j++) {
            auto n = p->neighbors[j];
            auto r = glm::length(p->position - n->position);

            if (r < h && r > 0) {
                avgVelocity -= 0.3f * (particleMass/n->density) * (p->velocity - n->velocity) * spiky()*pow(h-r,2.0f);
            }

        }
        */
        p->position += avgVelocity * deltaTime;
    }
}


float Simulation::poly6() {
    return 315.0f/(64.0f*pi*pow(h, 9.0f));
}

float Simulation::spiky() {
    return -45.0f/(pi*pow(h, 6.0f));;
}

