//
// Created by Édouard Gagné on 2020-10-15.
//

#include "Renderer.h"
#include "glm/gtc/matrix_transform.hpp"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

using namespace glm;
using namespace std;

Renderer::Renderer(Shader* shader, std::vector<Model*> models) {
    this->shader = shader;
    this->models = models;
}

void Renderer::render() {
    shader->use();
    // create transformations
    glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    // pass transformation matrices to the shader
    shader->setMat4("proj", projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
    shader->setMat4("view", view);
    for (auto & model : models) {
       model->draw(*shader);
    }
}

