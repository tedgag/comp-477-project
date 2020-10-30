//
// Created by Edouard on 2020-10-27.
//

#include <iostream>
#include "InstancedRenderer.h"

InstancedRenderer::InstancedRenderer(Shader *shader, Camera *camera, Model * model) {
    this->shader = shader;
    this->camera = camera;
    this->model = model;
    setup();
}

void InstancedRenderer::render(std::vector<glm::vec3> instances) {
    shader->use();
    camera->setShaderUniforms(shader);
    shader->setFloat("diffuseTexture", 0);
    glBindTexture(GL_TEXTURE_2D, model->mesh->texture);
    glActiveTexture(GL_TEXTURE0);
    glBindBuffer(GL_ARRAY_BUFFER, modelsBuffer);
    glBufferData(GL_ARRAY_BUFFER, instances.size() * sizeof(glm::vec3), &instances[0], GL_STATIC_DRAW);
    glBindVertexArray(model->mesh->VAO);
    glDrawElementsInstanced(GL_TRIANGLES, model->mesh->indices.size(), GL_UNSIGNED_INT, 0, instances.size());

}
void InstancedRenderer::setup() {
    glGenBuffers(1, &modelsBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, modelsBuffer);
    glBufferData(GL_ARRAY_BUFFER, 0 * sizeof(glm::vec3), nullptr, GL_STATIC_DRAW);
    GLuint VAO = model->mesh->VAO;
    glBindVertexArray(VAO);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void *)0);
    glVertexAttribDivisor(3, 1);

    glBindVertexArray(0);

}

