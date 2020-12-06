//
// Created by Édouard Gagné on 2020-10-15.
//

#include "Renderer.h"

#include <utility>
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>

using namespace glm;
using namespace std;

Renderer::Renderer(std::shared_ptr<Camera> camera) {
    this->camera = camera;
    sceneShader = std::make_shared<Shader>(
            "../resources/shaders/scene_shader.vert",
            "../resources/shaders/scene_shader.frag"
    );
    particleShader = std::make_shared<Shader>(
            "../resources/shaders/particles_shader.vert",
            "../resources/shaders/particles_shader.frag"
    );
    skyShader = std::make_shared<Shader>(
            "../resources/shaders/sky_shader.vert",
            "../resources/shaders/sky_shader.frag"
    );
    std::vector<std::string> faces {
            "../resources/assets/textures/skybox/mountain/px.png",
            "../resources/assets/textures/skybox/mountain/nx.png",
            "../resources/assets/textures/skybox/mountain/py.png",
            "../resources/assets/textures/skybox/mountain/ny.png",
            "../resources/assets/textures/skybox/mountain/pz.png",
            "../resources/assets/textures/skybox/mountain/nz.png",
    };
    boxModel = std::make_shared<Model>(
            std::make_shared<Mesh>("../resources/assets/models/box.obj"),
            glm::vec3(0.0f),
            glm::vec3(0.0f),
            glm::vec3(0.0f),
            glm::vec3(0.5f,0.5f,0.5f));

    particleModel = std::make_shared<Model>(std::make_shared<Mesh>("../resources/assets/models/sphere.obj"));
    sceneModels.push_back(boxModel);
    setupSkybox(faces);
    particlesBuffer = setupInstancedBuffer(particleModel);
}

void Renderer::render(std::vector<glm::vec3> positions, glm::vec3 particleColor, float particleRadius) {

    particleModel->color = particleColor;
    sceneShader->use();

    // Rendering skybox
    if(enableSkybox) {
        skyShader->use();
        camera->setShaderUniformsStatic(skyShader);
        glDepthFunc(GL_LEQUAL);
        glBindVertexArray(skyboxModel->mesh->VAO);
        glBindBuffer(GL_ARRAY_BUFFER, skyboxModel->mesh->VBO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxModel->mesh->texture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS);
    }
    // Rendering particles

    particleShader->use();
    camera->setShaderUniforms(particleShader);
    particleShader->setVec3("color", particleColor);
    particleShader->setFloat("size", particleRadius);
    glBindBuffer(GL_ARRAY_BUFFER, particlesBuffer);
    glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(glm::vec3), &positions[0], GL_STATIC_DRAW);
    glBindVertexArray(particleModel->mesh->VAO);
    glDrawElementsInstanced(GL_TRIANGLES, particleModel->mesh->indices.size(), GL_UNSIGNED_INT, 0, positions.size());

    // Rendering scene models
    if (enableBounds) {
        camera->setShaderUniforms(sceneShader);
        for (auto & model : sceneModels) {
            model->draw(*sceneShader, GL_TRIANGLES);
        }
    }
}

GLuint Renderer::setupInstancedBuffer(std::shared_ptr<Model>model) {
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 0 * sizeof(glm::vec3), nullptr, GL_STATIC_DRAW);
    GLuint VAO = model->mesh->VAO;
    glBindVertexArray(VAO);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void *)0);
    glVertexAttribDivisor(2, 1);

    glBindVertexArray(0);

    return buffer;
}

void Renderer::setupSkybox(std::vector<std::string> faces) {
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
    skyboxModel = std::make_shared<Model>(
            std::make_shared<Mesh>(
            "../resources/assets/models/cube.obj",
            faces,
            std::vector<Vertex>(skyboxVertices, skyboxVertices + sizeof skyboxVertices / sizeof skyboxVertices[0])
            ));
}

