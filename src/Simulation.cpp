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
                positions.push_back(glm::vec3((float)i/2,(float)j/2,(float)k/2) + offset);
            }
        }
    }
    grid = new Grid(glm::vec3(boundaries), 1.0f);
    sceneModels.push_back(boxModel);
    sceneRenderer = new Renderer(sceneShader, camera, sceneModels);
    particlesRenderer = new InstancedRenderer(particleShader, camera, particleModel, particleRadius);
    neighbors.resize(positions.size());
    velocities.resize(positions.size());
    accelerations.resize(positions.size());
}

void Simulation::run() {
    grid->findNeighbors(positions, particleRadius * 4, neighbors);

    computeForces();
    float deltaTime = 0.05f * particleRadius;
    timeIntegration(deltaTime);
    collisionHandling();
    particlesRenderer->render(positions);
    sceneRenderer->render();
}
void Simulation::computeForces() {
    #pragma omp parallel for
    for (int i =0 ; i<accelerations.size(); i++) {
        accelerations[i].y = g;
    }

}
void Simulation::timeIntegration( float deltaTime) {
    #pragma omp parallel for
    for (int i =0 ; i<positions.size(); i++) {
        velocities[i] += accelerations[i] * deltaTime;
        positions[i] += velocities[i] * deltaTime;
    }
}
void Simulation::collisionHandling() {
    #pragma omp parallel for
    for (int i =0 ; i<positions.size(); i++) {
        if (positions[i].x-displacement< 0.0f) {
            velocities[i].x *= boundDamping;
            positions[i].x = displacement;
        }
        if (positions[i].x + displacement >= boundaries.x) {
            velocities[i].x *= boundDamping;
            positions[i].x = boundaries.x - displacement;
        }
        if (positions[i].y -displacement< 0.0f) {
            velocities[i].y *= boundDamping;
            positions[i].y = displacement;
        }
        if (positions[i].y + displacement>= boundaries.y) {
            velocities[i].y *= boundDamping;
            positions[i].y = boundaries.y - displacement;
        }
        if (positions[i].z - displacement< 0.0f) {
            velocities[i].z *= boundDamping;
            positions[i].z = displacement;
        }
        if (positions[i].z + displacement >= boundaries.z) {
            velocities[i].z *= boundDamping;
            positions[i].z = boundaries.z - displacement;
        }
    }
}
