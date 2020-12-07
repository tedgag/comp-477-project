//
// Created by Édouard on 2020-12-03.
//

#include "Scene.h"

#include <iostream>
#include <utility>

Scene::Scene(const std::shared_ptr<Camera> & camera) {
    this->simulation =  std::make_shared<Simulation>(particleRadius);
    this->renderer = std::make_shared<Renderer>(camera);
    setBoundaries(glm::vec3(12.0f));
    setFluid(glm::vec3(6.0f), glm::vec3(20));
    setMass(particleMass);
    setViscosity(viscosity);
    setGravity(gravity);
    setSkybox(true);
    setBounds(true);
}

void Scene::render(float deltaTime) {
    if (play && start)
        simulation->run(deltaTime);
    std::vector<glm::vec3> positions;
    for (int i = 0; i < simulation->particles.size(); i++) {
        Particle *  p = simulation->particles[i];
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
    if (start || (newPosition == fluidPosition && newDimensions == fluidDimensions))
        return;

    if ((int) (newDimensions.x * newDimensions.y * newDimensions.z) > maxParticles)
        return;

    for (int i=0; i<3; i++) {
        if (newDimensions[i] * particleRadius + newPosition[i] > boundaries[i] ||
            newPosition[i] - newDimensions[i] * particleRadius < 0.0f ) {
            return;
        }
    }

    fluidPosition = newPosition;
    fluidDimensions = newDimensions;
    setFluid();
}
void Scene::setFluid() {
    for (int i =0; i <simulation->particles.size(); i++) {
        delete simulation->particles[i];
    }
    simulation->particles.clear();
    nbParticles = (int) (fluidDimensions.x * fluidDimensions.y * fluidDimensions.z);
    for (int i =0 ; i<(int)fluidDimensions.x ; i++) {
        for (int j =0; j<(int)fluidDimensions.y; j++) {
            for (int k =0; k<(int) fluidDimensions.z; k++) {
                Particle * p = new Particle;
                glm::vec3 pos = glm::vec3(
                        -fluidDimensions.x/2 + i + particleRadius,
                        -fluidDimensions.y/2 + j + particleRadius,
                        -fluidDimensions.z/2 + k + particleRadius);
                p->position = pos * particleRadius*2.0f + fluidPosition;
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
void Scene::setMass(float mass) {
    particleMass = mass;
    simulation->particleMass = mass;
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

void Scene::setSkybox(bool enabled) {
    enableSkybox = enabled;
    renderer->enableSkybox = enabled;
}
void Scene::setBounds(bool enabled) {
    enableBounds = enabled;
    renderer->enableBounds = enabled;
}

