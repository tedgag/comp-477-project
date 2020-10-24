//
// Created by Édouard Gagné on 2020-10-15.
//

#ifndef COMP477PROJECT_MODEL_H
#define COMP477PROJECT_MODEL_H

#include "Mesh.h"

class Model {
    public:
        Model();
        Model(Mesh * mesh, glm::vec3 position, glm::vec3 rotation, glm::vec3 scaling);
        glm::mat4 getModelMatrix() const;
        void draw(Shader& shader);
    private:
        Mesh * mesh;
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scaling;
};


#endif //COMP477PROJECT_MODEL_H
