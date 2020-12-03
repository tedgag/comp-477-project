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
        GLuint VAO = 0;
        GLuint VBO = 0;
        GLuint EBO = 0;
        GLuint texture = 0;
        Mesh();
        Mesh(const std::string& modelPath,
             const std::vector<std::string>& cubeMapFaces = std::vector<std::string>(),
                     std::vector<Vertex> vertices = std::vector<Vertex>());
        ~Mesh();
        void draw(Shader &shader, GLenum mode);
    private:
        void loadTexture(const std::string& path);
        void loadCubeMap(std::vector<std::string> faces);

        bool loadAssImp(const std::string& path);
};


#endif //COMP477PROJECT_MESH_H
