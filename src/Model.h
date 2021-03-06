//
// Created by Édouard Gagné on 2020-10-15.
//

#ifndef COMP477PROJECT_MODEL_H
#define COMP477PROJECT_MODEL_H

#include "Mesh.h"
#include <memory>

class Model {
    public:
        Model(std::shared_ptr<Mesh> mesh, glm::vec3 position, glm::vec3 rotation, glm::vec3 scaling, glm::vec3 color);
        Model(std::shared_ptr<Mesh> mesh, glm::vec3 color);
        Model(std::shared_ptr<Mesh> mesh);

    glm::mat4 getModelMatrix();
        void draw(Shader& shader, GLenum mode);
        std::shared_ptr<Mesh> mesh;
        glm::vec3 position = glm::vec3(0.0f);
        glm::vec3 rotation = glm::vec3(0.0f);
        glm::vec3 scaling = glm::vec3(1.0f);
        glm::vec3 color = glm::vec3(1.0f);
};


#endif //COMP477PROJECT_MODEL_H
