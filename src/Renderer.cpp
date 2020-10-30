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
    camera->setShaderUniforms(shader);
    for (auto & model : models) {
       model->draw(*shader);
    }
}
