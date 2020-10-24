//
// Created by Édouard Gagné on 2020-10-16.
//

#include "Simulation.h"

Simulation::Simulation() {
    const std::string vPath = "../resources/shaders/vShader.glsl";
    const std::string fPath = "../resources/shaders/fShader.glsl";

    auto* shader = new Shader(vPath, fPath);
    Mesh * m = new Mesh("../resources/assets/textures/cardboard.jpg", "../resources/assets/models/cube.obj");
    auto* model = new Model(m, glm::vec3(2.0f,5.0f,-30.0f), glm::vec3(45.0f,45.0f,0.0f), glm::vec3(5.0f,5.0f,5.0f));
    std::vector<Model *> cubeModels;
    cubeModels.push_back(model);

    renderer = new Renderer(shader, cubeModels);
}

void Simulation::run() {
    renderer->render();
}
