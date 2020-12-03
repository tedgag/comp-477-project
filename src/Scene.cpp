//
// Created by Édouard on 2020-12-03.
//

#include "Scene.h"

void Scene::render() {
    std::vector<glm::vec3> positions;
    for (int i = 0; i < simulation->particles.size(); i++) {
        Particle *p = simulation->particles[i];
        positions.push_back(p->position);
    }
    particleModel->color = particleColor;
    sceneShader->use();
    // Rendering skybox
    skyShader->use();
    camera->setShaderUniformsStatic(skyShader);
    glDepthFunc(GL_LEQUAL);
    glBindVertexArray(skyBoxModel->mesh->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyBoxModel->mesh->VBO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyBoxModel->mesh->texture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS);
    // Rendering particles
    particleShader->use();
    camera->setShaderUniforms(particleShader);
    particleShader->setVec3("color", particleColor);
    particleShader->setFloat("size", simulation->particleRadius);
    glBindBuffer(GL_ARRAY_BUFFER, particlesBuffer);
    glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(glm::vec3), &positions[0], GL_STATIC_DRAW);
    glBindVertexArray(particleModel->mesh->VAO);
    glDrawElementsInstanced(GL_TRIANGLES, particleModel->mesh->indices.size(), GL_UNSIGNED_INT, 0, positions.size());
    // Rendering scene models
    camera->setShaderUniforms(sceneShader);
    for (auto & model : sceneModels) {
        model->draw(*sceneShader, GL_TRIANGLES);
    }
}
void Scene::init() {
    sceneShader = new Shader(
            "../resources/shaders/scene_shader.vert",
            "../resources/shaders/scene_shader.frag"
    );
    particleShader = new Shader(
            "../resources/shaders/particles_shader.vert",
            "../resources/shaders/particles_shader.frag"
    );
    skyShader = new Shader(
            "../resources/shaders/sky_shader.vert",
            "../resources/shaders/sky_shader.frag"
    );
    std::vector<std::string> faces {
            "../resources/assets/textures/skybox/lake/px.png",
            "../resources/assets/textures/skybox/lake/nx.png",
            "../resources/assets/textures/skybox/lake/py.png",
            "../resources/assets/textures/skybox/lake/ny.png",
            "../resources/assets/textures/skybox/lake/pz.png",
            "../resources/assets/textures/skybox/lake/nz.png",
    };

    Mesh * particleMesh = new Mesh("../resources/assets/models/sphere.obj");
    Mesh * boxMesh = new Mesh("../resources/assets/models/box.obj");

    boxModel = new Model(
            boxMesh,
            glm::vec3(0.0f),
            glm::vec3(0.0f),
            glm::vec3(0.0f),
            glm::vec3(0.5f,0.5f,0.5f));

    particleModel = new Model(particleMesh, particleColor);

    sceneModels.push_back(boxModel);
    setupSkybox(faces);
    particlesBuffer = setupInstancedBuffer(particleModel);
    //gridRenderer = new InstancedRenderer(particleShader, camera, boxModel, h/2);
}

GLuint Scene::setupInstancedBuffer(Model * model) {
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

void Scene::setupSkybox(std::vector<std::string> faces) {
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
    skyBoxModel = new Model (skyMesh);
}
