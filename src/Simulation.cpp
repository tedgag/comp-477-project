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
    Model * boxModel = new Model(boxMesh,  (boxDimensions)/2.0f , glm::vec3(0.0f), (boxDimensions)/2.0f, particleColor);
    glm::vec3 offset = glm::vec3(1.5,1.5,1.5);
    glm::vec3 initialFluid = glm::vec3(10,20,10);
    for (int i =0 ; i<(int)initialFluid.x ; i++) {
        for (int j =0 ; j<(int)initialFluid.y; j++) {
            for (int k =0 ; k<(int)initialFluid.z ; k++) {
                positions.push_back(glm::vec3((float)i/2,(float)j/2,(float)k/2) + offset);
            }
        }
    }
    grid = new Grid(glm::vec3(boxDimensions), 1.0f);
    cellPositions = grid->getCellInstances();
    sceneModels.push_back(boxModel);
    sceneRenderer = new Renderer(sceneShader, camera, sceneModels);
    particlesRenderer = new InstancedRenderer(particleShader, camera, particleModel);
    neighbors.resize(positions.size());
}

void Simulation::run() {
    grid->findNeighbors(positions, particleRadius * 4, neighbors);
    sceneRenderer->render();

    particleShader->use();
    particleShader->setFloat("size", particleRadius);
    particlesRenderer->render(positions);
}
