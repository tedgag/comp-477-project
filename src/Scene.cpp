//
// Created by Édouard on 2020-12-03.
//

#include "Scene.h"

#include <iostream>

Scene::Scene(const std::shared_ptr<Camera> & camera) {
    this->simulation =  std::make_shared<Simulation>(particleRadius);
    this->renderer = std::make_shared<Renderer>(camera);
    setBoundaries(glm::vec3(16.0f));
    setFluid( boundaries/2.0f, glm::vec3(15));
}

void Scene::render() {
    if (play && start)
        simulation->run();
    std::vector<glm::vec3> positions;
    for (int i = 0; i < simulation->particles.size(); i++) {
        std::shared_ptr<Particle> p = simulation->particles[i];
        positions.push_back(p->position);
    }
    renderer->render(positions,particleColor,particleRadius);
}

void Scene::setBoundaries(glm::vec3 newBoundaries) {
    if (boundaries == newBoundaries)
        return;
    if (!start) {
        for (int i=0; i<3; i++) {
            if (newBoundaries[i] < fluidDimensions[i] * particleRadius + fluidPosition[i] - particleRadius * 2.0f)
                return;
        }
    }
    

    boundaries = newBoundaries;
    renderer->boxModel->position = boundaries/2.0f;
    renderer->boxModel->scaling = boundaries/2.0f;
    simulation->grid->resizeGrid(boundaries);
}
void Scene::setFluid(glm::vec3 newPosition, glm::vec3 newDimensions) {
    if (newPosition == fluidPosition && newDimensions == fluidDimensions)
        return;

    if (start || (int) (newDimensions.x * newDimensions.y * newDimensions.z) > maxParticles)
        return;

    for (int i=0; i<3; i++) {
        if (newDimensions[i] * particleRadius + newPosition[i] - particleRadius * 2.0f> boundaries[i] ||
            newPosition[i] - newDimensions[i] * particleRadius < 0.0f ) {
            return;
        }
    }

    fluidPosition = newPosition;
    fluidDimensions = newDimensions;
    setFluid();
}
void Scene::setFluid() {
    simulation->particles.clear();
    nbParticles = (int) (fluidDimensions.x * fluidDimensions.y * fluidDimensions.z);
    for (int i =-(int) fluidDimensions.x/2 ; i<(int) fluidDimensions.x/2 ; i++) {
        for (int j =-(int) fluidDimensions.y/2 ; j<(int) fluidDimensions.y/2; j++) {
            for (int k =-(int) fluidDimensions.z/2 ; k<(int) fluidDimensions.z/2 ; k++) {
                std::shared_ptr<Particle> p = std::make_shared<Particle>();
                p->position = glm::vec3((float)i,(float)j,(float)k) * particleRadius*2.0f + fluidPosition;
                simulation->particles.push_back(p);
            }
        }
    }
}
void Scene::setGravity(glm::vec3 grav) {
    gravity = grav;
    simulation->gravity = grav;
}

void Scene::setViscosity(float visc) {
    viscosity = visc;
    simulation->viscosity = visc;
}
void Scene::setColor(glm::vec3 color) {
    particleColor = color;
}
void Scene::reset() {
    play = false;
    start = false;
    setFluid();
    setBoundaries(savedParams.boundaries);
    setViscosity(savedParams.viscosity);
    setGravity(savedParams.gravity);
    setColor(savedParams.particleColor);
}

void Scene::save() {
    play = true;
    start = true;
    savedParams.boundaries = boundaries;
    savedParams.viscosity = viscosity;
    savedParams.gravity = gravity;
    savedParams.particleColor = particleColor;
}

