//
// Created by Édouard Gagné on 2020-10-16.
//

#include <iostream>
#include "Simulation.h"
#include <cmath>

Simulation::Simulation(Camera * camera) {
    sceneShader = new Shader(
            "../resources/shaders/scene_shader.vert",
            "../resources/shaders/scene_shader.frag"
            );
    particleShader = new Shader(
            "../resources/shaders/particles_shader.vert",
            "../resources/shaders/particles_shader.frag"
    );
    Mesh * particleMesh = new Mesh("../resources/assets/models/sphere.obj");
    Mesh * boxMesh = new Mesh("../resources/assets/models/box.obj");
    h = 3*particleRadius;
    hs = h * h;
    boundaries = glm::vec3(10.0f,25.0f,20.0f) * h;
    Model * particleModel = new Model(particleMesh, particleColor);
    Model * boxModel = new Model(
            boxMesh,
            (boundaries)/2.0f,
            glm::vec3(0.0f),
            (boundaries)/2.0f,
            glm::vec3(0.5f,0.5f,0.5f));
    glm::vec3 offset = glm::vec3(boundaries.x/2.0f,6.0f, 1.90f);
    glm::vec3 initialFluid = glm::vec3(20, 30,10);
    for (int i =-(int)initialFluid.x/2 ; i<(int)initialFluid.x/2 ; i++) {
        for (int j =-(int)initialFluid.y/2 ; j<(int)initialFluid.y/2; j++) {
            for (int k =-(int)initialFluid.z/2 ; k<(int)initialFluid.z/2 ; k++) {
                auto * p = new Particle();
                p->position = glm::vec3((float)i,(float)j,(float)k) * particleRadius*1.5f+ offset;
                particles.push_back(p);
            }
        }
    }
    grid = new Grid(boundaries, h, particleRadius);

    sceneModels.push_back(boxModel);
    sceneRenderer = new Renderer(sceneShader, camera, sceneModels);
    particlesRenderer = new InstancedRenderer(particleShader, camera, particleModel, particleRadius);
    gridRenderer = new InstancedRenderer(particleShader, camera, boxModel, h/2);
}

void Simulation::run() {

    grid->findNeighbors(particles, h);
    computeDensityPressure();
    float deltaTime = 0.05f * particleRadius;
    computeForces(deltaTime);
    timeIntegration(deltaTime);
    grid->collisionHandling(particles);
    std::vector<glm::vec3> positions;
    for (int i =0 ; i<particles.size(); i++) {
        auto * p = particles[i];



        positions.push_back(p->position);
    }
    particlesRenderer->render(positions);

    //gridRenderer->render(grid->getCellInstances());
    sceneRenderer->render();
}
void Simulation::computeDensityPressure() {
    #pragma omp parallel for
    for (int i =0 ; i<particles.size(); i++) {
        auto p = particles[i];
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
void Simulation::computeForces(float deltaTime) {
    #pragma omp parallel for
    for (int i =0 ; i<particles.size(); i++) {
        auto accel = glm::vec3(0.0f);

        auto p = particles[i];

        float kp = p->pressure / (p->density * p->density);
        for (int j =0 ; j<p->neighbors.size(); j++) {
            auto n = p->neighbors[j];
            auto r = glm::length(p->position - n->position);
            float r2 = r * r;
            if (r2 <= hs && r2 > 0) {
                // Pressure forces
                float kn = n->pressure / (n->density * n->density);
                float k = (kp + kn);
                // momentum equation
                accel -= glm::normalize(p->position - n->position)* k * spiky()*pow(hs-r2,2.0f);

                // Viscosity
                accel += viscosity*(n->velocity - p->velocity)/n->density * poly6()*pow(hs-r2, 3.0f);
            }

        }
        for(int j = 0; j< p->ghosts.size(); j++) {

            auto gDist = p->ghosts[j];
            auto r = glm::length(gDist);
            float r2 = r * r;
            if (r2 <= hs && r2 > 0) {
                accel -= glm::normalize(gDist) * kp*spiky()*pow(hs-r2,2.0f);
            }
        }
        // Gravity
        accel *= particleMass;
        accel .y += G;
        particles[i]->acceleration = accel;

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
