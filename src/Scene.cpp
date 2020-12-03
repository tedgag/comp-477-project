//
// Created by Édouard on 2020-12-03.
//

#include "Scene.h"
#include <iostream>

Scene::Scene(Camera *camera) {
    this->simulation = new Simulation(particleRadius);
    this->camera = camera;
    this->renderer = new Renderer(camera);
    setBoundaries(glm::vec3(20.0f));
    setFluid( gridBoundaries/2.0f, glm::vec3(20));
}

void Scene::render() {
    if (play && start)
        simulation->run();
    std::vector<glm::vec3> positions;
    for (int i = 0; i < simulation->particles.size(); i++) {
        Particle *p = simulation->particles[i];
        positions.push_back(p->position);
    }
    renderer->render(positions,particleColor,particleRadius);
}

void Scene::setBoundaries(glm::vec3 newDimensions) {
    if (gridDimensions == newDimensions) {
        return;
    }

    glm::vec3 newBoundaries = newDimensions * simulation->h;
    for (int i=0; i<3; i++) {
        if (newBoundaries[i] < fluidDimensions[i] * particleRadius + fluidPosition[i] - particleRadius * 2.0f)
            return;
    }

    gridDimensions = newDimensions;
    gridBoundaries = newBoundaries;
    renderer->boxModel->position = gridBoundaries/2.0f;
    renderer->boxModel->scaling = gridBoundaries/2.0f;
    simulation->grid->updateBoundaries(gridBoundaries, gridDimensions);
}
void Scene::setFluid(glm::vec3 newPosition, glm::vec3 newDimensions) {
    if (newPosition == fluidPosition && newDimensions == fluidDimensions)
        return;

    if ((int) (newDimensions.x * newDimensions.y * newDimensions.z) > maxParticles)
        return;

    for (int i=0; i<3; i++) {
        if (newDimensions[i] * particleRadius + newPosition[i] - particleRadius * 2.0f> gridBoundaries[i] ||
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
                auto * p = new Particle();
                p->position = glm::vec3((float)i,(float)j,(float)k) * particleRadius*2.0f + fluidPosition;
                simulation->particles.push_back(p);
            }
        }
    }
}

