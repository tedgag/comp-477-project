//
// Created by Édouard Gagné on 2020-10-15.
//

#ifndef COMP477PROJECT_RENDERER_H
#define COMP477PROJECT_RENDERER_H

#include "Model.h"
#include "Camera.h"

class Renderer {
    public:
        Renderer(Camera* camera);
        void render(std::vector<glm::vec3> positions, glm::vec3 particleColor, float particleRadius);
        Model * boxModel;
    private:
        GLuint setupInstancedBuffer(Model * model);
        void setupSkybox( std::vector<std::string> faces);
        Shader* shader;
        Camera* camera;
        std::vector<Model*> models;
        GLuint particlesBuffer;
        Model * particleModel;
        Model * skyBoxModel;
        std::vector<Model *> sceneModels;
        Shader * sceneShader;
        Shader * particleShader;
        Shader * skyShader;
};


#endif //COMP477PROJECT_RENDERER_H
