//
// Created by Édouard Gagné on 2020-10-15.
//

#include "Renderer.h"

#include <utility>
#include "glm/gtc/matrix_transform.hpp"


using namespace glm;
using namespace std;

Renderer::Renderer(Shader* shader, Camera* camera, std::vector<Model*> models) {
    this->shader = shader;
    this->models = std::move(models);
    this->camera = camera;
}

void Renderer::render() {
    shader->use();
    glm::mat4 proj = glm::mat4(1.0f);
    proj = glm::perspective(camera->zoomFactor, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.01f, 1000.0f);
    shader->setMat4("proj", proj);
    camera->setViewMatrix(shader);
    for (auto & model : models) {
       model->draw(*shader);
    }
}
