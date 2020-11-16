//
// Created by Édouard Gagné on 2020-10-16.
//

#include <iostream>
#include "Simulation.h"
#include <algorithm>
#include <execution>

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
    Model * particleModel = new Model(particleMesh, particleColor);
    Model * boxModel = new Model(boxMesh,  (boundaries)/2.0f , glm::vec3(0.0f), (boundaries)/2.0f, particleColor);
    glm::vec3 offset = glm::vec3(1.5,1.5,1.5);
    glm::vec3 initialFluid = glm::vec3(10,20,10);
    for (int i =0 ; i<(int)initialFluid.x ; i++) {
        for (int j =0 ; j<(int)initialFluid.y; j++) {
            for (int k =0 ; k<(int)initialFluid.z ; k++) {
                auto * p = new Particle();
                p->position = glm::vec3((float)i/2,(float)j/2,(float)k/2) + offset;
                particles.push_back(p);
            }
        }
    }
    grid = new Grid(glm::vec3(boundaries), 1.0f);
    sceneModels.push_back(boxModel);
    sceneRenderer = new Renderer(sceneShader, camera, sceneModels);
    particlesRenderer = new InstancedRenderer(particleShader, camera, particleModel, particleRadius);
}

void Simulation::run() {
    grid->findNeighbors(particles, particleRadius * 4);

    computeForces();
    float deltaTime = 0.05f * particleRadius;
    timeIntegration(deltaTime);
    collisionHandling();
    std::vector<glm::vec3> positions;
    for (auto & p : particles) {
        positions.push_back(p->position);
    }
    particlesRenderer->render(positions);
    sceneRenderer->render();
}
void Simulation::computeForces() {
    #pragma omp parallel for
    for (int i =0 ; i<particles.size(); i++) {
        //particles[i]->acceleration.y = g;
    }

}
void Simulation::timeIntegration( float deltaTime) {
    #pragma omp parallel for
    for (int i =0 ; i<particles.size(); i++) {
        particles[i]->velocity += particles[i]->acceleration * deltaTime;
        particles[i]->position += particles[i]->velocity * deltaTime;
    }
}
void Simulation::collisionHandling() {
    #pragma omp parallel for
    for (int i =0 ; i<particles.size(); i++) {
        if (particles[i]->position.x-displacement< 0.0f) {
            particles[i]->velocity.x *= boundDamping;
            particles[i]->position.x = displacement;
        }
        if (particles[i]->position.x + displacement >= boundaries.x) {
            particles[i]->velocity.x *= boundDamping;
            particles[i]->position.x = boundaries.x - displacement;
        }
        if (particles[i]->position.y -displacement< 0.0f) {
            particles[i]->velocity.y *= boundDamping;
            particles[i]->position.y = displacement;
        }
        if (particles[i]->position.y + displacement>= boundaries.y) {
            particles[i]->velocity.y *= boundDamping;
            particles[i]->position.y = boundaries.y - displacement;
        }
        if (particles[i]->position.z - displacement< 0.0f) {
            particles[i]->velocity.z *= boundDamping;
            particles[i]->position.z = displacement;
        }
        if (particles[i]->position.z + displacement >= boundaries.z) {
            particles[i]->velocity.z *= boundDamping;
            particles[i]->position.z = boundaries.z - displacement;
        }
    }
}
