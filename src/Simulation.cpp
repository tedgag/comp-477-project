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
    skyShader = new Shader(
            "../resources/shaders/sky_shader.vert",
            "../resources/shaders/sky_shader.frag"
    );
    std::vector<std::string> faces {
                    "../resources/assets/textures/skybox/lake/px.png",
                    "../resources/assets/textures/skybox/lake/nx.png",
                    "../resources/assets/textures/skybox/lake/py.png",
                    "../resources/assets/textures/skybox/lake/ny.png",
                    "../resources/assets/textures/skybox/lake/pz.png",
                    "../resources/assets/textures/skybox/lake/nz.png",
            };

    Mesh * particleMesh = new Mesh("../resources/assets/models/sphere.obj");
    Mesh * boxMesh = new Mesh("../resources/assets/models/box.obj");


    h = 4*particleRadius;
    hs = h * h;
    grid = new Grid( h, particleRadius);
    boxModel = new Model(
            boxMesh,
            glm::vec3(0.0f),
            glm::vec3(0.0f),
            glm::vec3(0.0f),
            glm::vec3(0.5f,0.5f,0.5f));

    setBoundaries(glm::vec3(14.0f,20.0f,20.0f));
    setFluid(gridBoundaries/2.0f,glm::vec3(21, 27,12));

    particleModel = new Model(particleMesh, particleColor);


    sceneModels.push_back(boxModel);
    sceneRenderer = new Renderer(sceneShader, camera, sceneModels);
    particlesRenderer = new InstancedRenderer(particleShader, camera, particleModel, particleRadius);
    gridRenderer = new InstancedRenderer(particleShader, camera, boxModel, h/2);
    skyRenderer = new SkyRenderer(skyShader, camera, faces);
}

void Simulation::run() {
    if (play && start) {
        grid->findNeighbors(particles, h);
        computeDensityPressure();
        float deltaTime = 0.05f * particleRadius;
        computeForces();
        timeIntegration(deltaTime);
        grid->collisionHandling(particles);
    }
    std::vector<glm::vec3> positions;
    for (int i = 0; i < particles.size(); i++) {
        Particle *p = particles[i];
        positions.push_back(p->position);
    }
    particleModel->color = particleColor;
    skyRenderer->render();
    particlesRenderer->render(positions);
    //gridRenderer->render(grid->getCellInstances());
    sceneRenderer->render();
}
void Simulation::computeDensityPressure() {
    #pragma omp parallel for
    for (int i =0 ; i<particles.size(); i++) {
        Particle * p = particles[i];
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
void Simulation::computeForces() {
    #pragma omp parallel for
    for (int i =0 ; i<particles.size(); i++) {
        glm::vec3 accel = glm::vec3(0.0f,0.0f,0.0f);

        Particle * p = particles[i];

        float kp = p->pressure / (p->density * p->density);
        for (int j =0 ; j<p->neighbors.size(); j++) {
            Particle * n = p->neighbors[j];
            float r = glm::length(p->position - n->position);
            float r2 = r * r;
            if (r2 <= hs && r2 > 0) {
                // Pressure forces
                float kn = n->pressure / (n->density * n->density);
                float k = (kp + kn);
                // momentum equation
                accel -= glm::normalize(p->position - n->position)* k * spiky()*(float)pow(hs-r2,2.0f);

                // Viscosity
                accel += viscosity*(n->velocity - p->velocity)/n->density * poly6()*(float)pow(hs-r2, 3.0f);
            }

        }

        for(int j = 0; j< p->ghosts.size(); j++) {

            auto gDist = p->ghosts[j];
            auto r = glm::length(gDist);
            float r2 = r * r;
            if (r2 <= hs && r2 > 0) {
                accel -= glm::normalize(gDist) * kp*spiky()*(float)pow(hs-r2,2.0f);
            }
        }

        // Gravity
        accel *= particleMass;
        accel .y += G;
        p->acceleration = accel;

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

void Simulation::setBoundaries(glm::vec3 newDimensions) {
    if (gridDimensions == newDimensions) {
        return;
    }

    glm::vec3 newBoundaries = newDimensions * h;
    for (int i=0; i<3; i++) {
        if (newBoundaries[i] < fluidDimensions[i] * particleRadius + fluidPosition[i] - particleRadius * 2.0f)
            return;
    }

    gridDimensions = newDimensions;
    gridBoundaries = newBoundaries;
    boxModel->position = gridBoundaries/2.0f;
    boxModel->scaling = gridBoundaries/2.0f;
    grid->updateBoundaries(gridBoundaries, gridDimensions);
}
void Simulation::setFluid(glm::vec3 newPosition, glm::vec3 newDimensions) {
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
void Simulation::setFluid() {
    particles.clear();
    nbParticles = (int) (fluidDimensions.x * fluidDimensions.y * fluidDimensions.z);
    for (int i =-(int) fluidDimensions.x/2 ; i<(int) fluidDimensions.x/2 ; i++) {
        for (int j =-(int) fluidDimensions.y/2 ; j<(int) fluidDimensions.y/2; j++) {
            for (int k =-(int) fluidDimensions.z/2 ; k<(int) fluidDimensions.z/2 ; k++) {
                auto * p = new Particle();
                p->position = glm::vec3((float)i,(float)j,(float)k) * particleRadius*2.0f + fluidPosition;
                particles.push_back(p);
            }
        }
    }
}