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

void InstancedRenderer::render(std::vector<glm::mat4> instances) {
    shader->use();
    glm::mat4 proj = glm::mat4(1.0f);
    proj = glm::perspective(camera->zoomFactor, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.01f, 1000.0f);
    shader->setMat4("proj", proj);
    camera->setViewMatrix(shader);
    shader->setFloat("diffuseTexture", 0);
    glBindTexture(GL_TEXTURE_2D, model->mesh->texture);
    glActiveTexture(GL_TEXTURE0);
    glBindBuffer(GL_ARRAY_BUFFER, modelsBuffer);
    glBufferData(GL_ARRAY_BUFFER, instances.size() * sizeof(glm::mat4), &instances[0], GL_STATIC_DRAW);
    glBindVertexArray(model->mesh->VAO);
    glDrawElementsInstanced(GL_TRIANGLES, model->mesh->indices.size(), GL_UNSIGNED_INT, 0, instances.size());

}
void InstancedRenderer::setup() {
    glGenBuffers(1, &modelsBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, modelsBuffer);
    glBufferData(GL_ARRAY_BUFFER, 0 * sizeof(glm::mat4), nullptr, GL_STATIC_DRAW);
    GLuint VAO = model->mesh->VAO;
    glBindVertexArray(VAO);
    // set attribute pointers for matrix (4 times vec4)
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *) 0);
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *) (sizeof(glm::vec4)));
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *) (2 * sizeof(glm::vec4)));
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *) (3 * sizeof(glm::vec4)));

    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
    glVertexAttribDivisor(6, 1);

    glBindVertexArray(0);

}

