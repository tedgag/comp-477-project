//
// Created by Édouard Gagné on 2020-10-15.
//

#include <iostream>
#include <utility>
#include "Model.h"
#include "glm/gtc/matrix_transform.hpp"

using namespace glm;
using namespace std;

Model::Model(std::shared_ptr<Mesh> mesh,glm::vec3 position,glm::vec3 rotation,glm::vec3 scaling,glm::vec3 color) :
             mesh{mesh}, position{position},rotation{rotation}, scaling{scaling}, color{color} {}

Model::Model(std::shared_ptr<Mesh> mesh, glm::vec3 color) :  mesh{mesh} , color{color} {}

Model::Model(std::shared_ptr<Mesh> mesh) :  mesh{mesh} {}

glm::mat4 Model::getModelMatrix() {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, scaling);
    return model;
}

void Model::draw(Shader &shader, GLenum mode) {
    glm::mat4 model = getModelMatrix();
    shader.setMat4("model", model);
    shader.setVec3("color", color);
    mesh->draw(shader, mode);
}


