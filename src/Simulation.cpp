//
// Created by Édouard Gagné on 2020-10-16.
//

#include <iostream>
#include "Simulation.h"

Simulation::Simulation(Camera * camera) {
    auto* sceneShader = new Shader(
            "../resources/shaders/scene_shader.vert",
            "../resources/shaders/scene_shader.frag"
            );
    auto* particlesShader = new Shader(
            "../resources/shaders/particles_shader.vert",
            "../resources/shaders/particles_shader.frag"
    );
    Mesh * particleMesh = new Mesh(
            "../resources/assets/textures/blue.jpg",
            "../resources/assets/models/sphere.obj"
            );
    particleModel = new Model(particleMesh);
    for (int i =0 ; i<10 ; i++) {
        for (int j =0 ; j<10 ; j++) {
            for (int k =0 ; k<10 ; k++) {
                Particle * particle = new Particle();
                particle->position = glm::vec3((float)i/10,(float)j/10,(float)k/10);
                particles.push_back(particle);
            }
        }
    }
    grid = new Grid(glm::vec3(64.0f,64.0f,64.0f), 0.5f);

    sceneModels.push_back(particleModel);
    sceneRenderer = new Renderer(sceneShader, camera, sceneModels);
    particlesRenderer = new InstancedRenderer(particlesShader, camera, particleModel);

}

void Simulation::run() {
    grid->buildHashTable(particles);
    std::vector<glm::vec3> positions;
    for (auto & particle : particles) {
        //particle.position += glm::vec3(0.0f, 0.01f, 0.0f);
        particle->neighbors = grid->findNeighbors(particle, 0.5f);
        positions.push_back(particle->position);
    }
    //sceneRenderer->render();
    particlesRenderer->render(positions);
}
