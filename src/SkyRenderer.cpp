//
// Created by Édouard on 2020-12-02.
//

#include "SkyRenderer.h"

#include <utility>

SkyRenderer::SkyRenderer(Shader *shader, Camera *camera, std::vector<std::string> faces):
    shader{shader}, camera{camera}, faces{std::move(faces)} {
    setup();
}

void SkyRenderer::setup() {
    Vertex skyboxVertices[] = {
            {glm::vec3(-1.0f,  1.0f, -1.0f)},
            {glm::vec3(-1.0f, -1.0f, -1.0f)},
            {glm::vec3(1.0f, -1.0f, -1.0f)},
            {glm::vec3(1.0f, -1.0f, -1.0f)},
            {glm::vec3(1.0f,  1.0f, -1.0f)},
            {glm::vec3(-1.0f,  1.0f, -1.0f)},

            {glm::vec3(-1.0f, -1.0f, 1.0f)},
            {glm::vec3(-1.0f, -1.0f, -1.0f)},
            {glm::vec3(-1.0f, 1.0f, -1.0f)},
            {glm::vec3(-1.0f, 1.0f, -1.0f)},
            {glm::vec3(-1.0f, 1.0f, 1.0f)},
            {glm::vec3(-1.0f, -1.0f, 1.0f)},

            {glm::vec3(1.0f, -1.0f, -1.0f)},
            {glm::vec3(1.0f, -1.0f, 1.0f)},
            {glm::vec3(1.0f, 1.0f, 1.0f)},
            {glm::vec3(1.0f, 1.0f, 1.0f)},
            {glm::vec3(1.0f, 1.0f, -1.0f)},
            {glm::vec3(1.0f, -1.0f, -1.0f)},

            {glm::vec3(-1.0f, -1.0f, 1.0f)},
            {glm::vec3(-1.0f, 1.0f, 1.0f)},
            {glm::vec3(1.0f, 1.0f, 1.0f)},
            {glm::vec3(1.0f, 1.0f, 1.0f)},
            {glm::vec3(1.0f, -1.0f, 1.0f)},
            {glm::vec3(-1.0f, -1.0f, 1.0f)},

            {glm::vec3(-1.0f, 1.0f, -1.0f)},
            {glm::vec3(1.0f, 1.0f, -1.0f)},
            {glm::vec3(1.0f, 1.0f, 1.0f)},
            {glm::vec3(1.0f, 1.0f, 1.0f)},
            {glm::vec3(-1.0f, 1.0f, 1.0f)},
            {glm::vec3(-1.0f, 1.0f, -1.0f)},

            {glm::vec3(-1.0f, -1.0f, -1.0f)},
            {glm::vec3(-1.0f, -1.0f, 1.0f)},
            {glm::vec3(1.0f, -1.0f, -1.0f)},
            {glm::vec3(1.0f, -1.0f, -1.0f)},
            {glm::vec3(-1.0f, -1.0f, 1.0f)},
            {glm::vec3(1.0f, -1.0f, 1.0f)},
    };
    Mesh * skyMesh = new Mesh("../resources/assets/models/cube.obj",faces,std::vector<Vertex>(skyboxVertices, skyboxVertices + sizeof skyboxVertices / sizeof skyboxVertices[0]));
    model = new Model (skyMesh);
}

void SkyRenderer::render() {
    shader->use();
    camera->setShaderUniformsStatic(shader);
    glDepthFunc(GL_LEQUAL);
    glBindVertexArray(model->mesh->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, model->mesh->VBO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, model->mesh->texture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS);
}
