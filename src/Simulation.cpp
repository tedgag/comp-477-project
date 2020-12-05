//
// Created by Édouard Gagné on 2020-10-16.
//

#include <iostream>
#include "Simulation.h"
#include <cmath>

Simulation::Simulation(float particleRadius) {
    this->particleRadius = particleRadius;
    h = 3*particleRadius;
    hs = h * h;
    grid = new Grid( h, particleRadius);
}

void Simulation::run(float deltaTime) {

    grid->collisionHandling(particles);
    grid->findNeighbors(particles, h);
    computeDensityPressure();
    float step;
    if (deltaTime < 0.05f) {
        step = 2.0f * deltaTime * particleRadius;
    } else {
        step = 0.1f * particleRadius;
    }
    computeForces();
    timeIntegration(step);

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
                // Density
                p->density += poly6()*pow(hs-r2, 3.0f);
            }
        }

        p->density *= particleMass;

        // Pressure
        float ratio = p->density/restDensity;
        if(ratio < 1.0f) {
            p->pressure = 0.0f;
        } else {
            p->pressure = pow(ratio, 7.0f) -1.0f;
        }
    }
}
void Simulation::computeForces() {
    #pragma omp parallel for
    for (int i =0 ; i<particles.size(); i++) {
        glm::vec3 accel = glm::vec3(0.0f,0.0f,0.0f);

        Particle * p = particles[i];
        float kp = p->pressure / (p->density * p->density);
        // Regular neighbors
        for (int j =0 ; j<p->neighbors.size(); j++) {
            Particle * n = p->neighbors[j];
            float r = glm::length(p->position - n->position);
            float r2 = r * r;
            if (r2 <= hs && r2 > 0) {
                // Pressure force
                float kn = n->pressure / (n->density * n->density);
                float k = (kp + kn);
                accel -= glm::normalize(p->position - n->position)* k * spiky()*(float)pow(h-r,2.0f);

                // Viscosity force
                accel += viscosity*(n->velocity - p->velocity)/n->density * poly6()*(float)pow(hs-r2, 3.0f);
            }

        }

        // Ghost neighbors (only check for pressure force)
        for(int j = 0; j< p->ghosts.size(); j++) {
            auto gDist = p->ghosts[j];
            auto r = glm::length(gDist);
            float r2 = r * r;
            if (r2 <= hs && r2 > 0) {
                accel -= glm::normalize(gDist) * kp*spiky()*(float)pow(h-r,2.0f);
            }
        }

        // Gravitational force
        accel *= particleMass;
        accel += gravity;
        p->acceleration = accel;

    }

}
void Simulation::timeIntegration( float deltaTime) {
    #pragma omp parallel for
    for (int i =0 ; i<particles.size(); i++) {
        auto * p = particles[i];
        p->velocity += p->acceleration * deltaTime;
        p->position += p->velocity * deltaTime;
    }
}


float Simulation::poly6() {
    return 315.0f/(64.0f*pi*pow(h, 9.0f));
}

float Simulation::spiky() {
    return -45.0f/(pi*pow(h, 6.0f));;
}

