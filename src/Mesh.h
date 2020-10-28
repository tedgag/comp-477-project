//
// Created by Édouard Gagné on 2020-10-15.
//

#ifndef COMP477PROJECT_MESH_H
#define COMP477PROJECT_MESH_H

#include "helpers/IncludeHeader.h"

#include <string>
#include <vector>

#include "Shader.h"

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};


class Mesh {
    public:
        // mesh data
        std::vector<Vertex> vertices;

        std::vector<unsigned int> indices;
        GLuint texture;
        GLuint VAO,VBO,EBO = 0;
        Mesh();
        Mesh(const std::string& imagePath, const std::string& modelPath);
        ~Mesh();
        void draw(Shader &shader);
    private:

        GLuint loadTexture(const std::string& path);
        bool loadAssImp(const std::string& path);
};


#endif //COMP477PROJECT_MESH_H
