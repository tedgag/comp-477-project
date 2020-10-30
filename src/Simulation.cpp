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
    for (int i =0 ; i<40 ; i++) {
        for (int j =0 ; j<40 ; j++) {
            for (int k =0 ; k<40 ; k++) {
                Particle particle;
                particle.position = glm::vec3((float)i,(float)j,(float)k);
                particles.push_back(particle);
            }
        }
    }
    sceneModels.push_back(particleModel);
    sceneRenderer = new Renderer(sceneShader, camera, sceneModels);
    particlesRenderer = new InstancedRenderer(particlesShader, camera, particleModel);
}

void Simulation::run() {
    std::vector<glm::vec3> positions;
    for (auto & particle : particles) {

        //particle.position += glm::vec3(0.0f, 0.01f, 0.0f);
        positions.push_back(particle.position);

    }
    //sceneRenderer->render();
    particlesRenderer->render(positions);
}
