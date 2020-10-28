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
            "../resources/assets/textures/cardboard.jpg",
            "../resources/assets/models/sphere.obj"
            );
    particleModel = new Model(particleMesh);
    for (int i =0 ; i<40 ; i++) {
        for (int j =0 ; j<40 ; j++) {
            for (int k =0 ; k<40 ; k++) {
                Particle particle;
                particle.position = glm::vec3((float)i,(float)j,(float)k);
                particle.scaling = glm::vec3(0.1f,0.1f,0.1f);
                particles.push_back(particle);
            }
        }
    }
    sceneModels.push_back(particleModel);
    sceneRenderer = new Renderer(sceneShader, camera, sceneModels);
    particlesRenderer = new InstancedRenderer(particlesShader, camera, particleModel);
}

void Simulation::run() {
    std::vector<glm::mat4> particleInstances;
    for (auto & particle : particles) {
        glm::mat4 model = glm::mat4(1.0f);
        particle.position += glm::vec3(0.0f, 0.01f, 0.0f);
        model = glm::translate(model, particle.position);
        model = glm::scale(model, particle.scaling);
        particleInstances.push_back(model);
    }
    particlesRenderer->render(particleInstances);

    //sceneRenderer->render();
}
