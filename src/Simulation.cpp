//
// Created by Édouard Gagné on 2020-10-16.
//

#include <iostream>
#include "Simulation.h"
#include <cmath>

Simulation::Simulation(float particleRadius) {
    this->particleRadius = particleRadius;
    h = 0.6f;
    hs = h * h;
    timeStep = 0.02;
    grid = new Grid( h, particleRadius);
    poly6 = 315.0f/(64.0f*pi*pow(h, 9.0f));
    spiky = -45.0f/(pi*pow(h, 6.0f));
}

void Simulation::run(float deltaTime) {
    grid->collisionHandling(particles);
    grid->findNeighbors(particles, h);
    computeDensityPressure();
    computeForces();
    timeIntegration(timeStep);
}
void Simulation::computeDensityPressure() {
    #pragma omp parallel for
    for (int i =0 ; i<particles.size(); i++) {
        const auto p = particles[i];
        // Initial density cannot be zero
        p->density = pow(hs, 3.0f);
        for(int j =0 ; j<p->neighbors.size(); j++)
        {
            const auto n = p->neighbors[j];
            const auto r = p->position - n->position;
            const float r2 = glm::length(r) * glm::length(r);
            if(r2 < hs)
            {
                // Density
                p->density += poly6*pow(hs-r2, 3.0f);
            }
        }

        p->density *= particleMass;
        // Pressure
        const float ratio = p->density/restDensity;
        // The ratio has to be greater than one so the pressure is not negative
        if(ratio < 1.0f) {
            p->pressure = 0.0f;
        } else {
            p->pressure = pressureConstant * (pow(ratio, 7.0f) - 1.0f);
        }
    }
}
void Simulation::computeForces() {
    #pragma omp parallel for
    for (int i =0 ; i<particles.size(); i++) {
        glm::vec3 accel = glm::vec3(0.0f,0.0f,0.0f);

        const auto  p = particles[i];
        const float kp = p->pressure / (p->density * p->density);
        // Regular neighbors
        for (int j =0 ; j<p->neighbors.size(); j++) {
            const auto n = p->neighbors[j];
            const float r = glm::length(p->position - n->position);
            const float r2 = r * r;
            if (r2 <= hs && r2 > 0) {
                // Pressure force
                const float kn = n->pressure / (n->density * n->density);
                const float k = (kp + kn);
                accel -= glm::normalize(p->position - n->position)* k * spiky*(float)pow(h-r,2.0f)/p->density;
                // Viscosity force
                accel += viscosity*(n->velocity - p->velocity)/n->density * poly6*(float)pow(hs-r2, 3.0f);
            }

        }

        // Ghost neighbors (only check for pressure force)
        for(int j = 0; j< p->ghosts.size(); j++) {
            const auto gDist = p->ghosts[j];
            const auto r = glm::length(gDist);
            const float r2 = r * r;
            if (r2 <= hs && r2 > 0) {
                accel -= glm::normalize(gDist) * kp*spiky*(float)pow(h-r,2.0f)/p->density;
            }
        }
        // Constant terms
        accel *= particleMass;
        // Gravitational force
        accel += gravity;
        p->acceleration = accel;
    }
}
void Simulation::timeIntegration( float deltaTime) {
    #pragma omp parallel for
    for (int i =0 ; i<particles.size(); i++) {
        const auto p = particles[i];
        p->velocity += p->acceleration * deltaTime;
        p->position += p->velocity * deltaTime;
    }
}

