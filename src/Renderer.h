//
// Created by Édouard Gagné on 2020-10-15.
//

#ifndef COMP477PROJECT_RENDERER_H
#define COMP477PROJECT_RENDERER_H

#include "Model.h"
#include "Camera.h"
#include <memory>
class Renderer {
    public:
        Renderer(std::shared_ptr<Camera> camera);
        void render(std::vector<glm::vec3> positions, glm::vec3 particleColor, float particleRadius);
        std::shared_ptr<Model> boxModel;
        bool enableSkybox, enableBounds;
    private:
        GLuint setupInstancedBuffer(std::shared_ptr<Model> model);
        void setupSkybox( std::vector<std::string> faces);
        std::shared_ptr<Camera> camera;
        std::vector<std::shared_ptr<Model>> models;
        GLuint particlesBuffer;
        std::shared_ptr<Model> particleModel;
        std::shared_ptr<Model> skyboxModel;
        std::vector<std::shared_ptr<Model>> sceneModels;
        std::shared_ptr<Shader> sceneShader;
        std::shared_ptr<Shader> particleShader;
        std::shared_ptr<Shader> skyShader;
};


#endif //COMP477PROJECT_RENDERER_H
