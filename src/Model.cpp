//
// Created by Édouard Gagné on 2020-10-15.
//

#include <iostream>
#include "Model.h"
#include "glm/gtc/matrix_transform.hpp"

using namespace glm;
using namespace std;

Model::Model(Mesh * mesh, glm::vec3 position, glm::vec3 rotation, glm::vec3 scaling) {
    this->mesh = mesh;
    this->position = position;
    this->rotation = rotation;
    this->scaling = scaling;
}
Model::Model(Mesh * mesh) {
    this->mesh = mesh;
}

glm::mat4 Model::getModelMatrix() {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, scaling);
    return model;
}

void Model::draw(Shader &shader) {
    glm::mat4 model = getModelMatrix();
    shader.setMat4("model", model);
    mesh->draw(shader);
}


