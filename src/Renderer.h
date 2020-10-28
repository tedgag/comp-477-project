//
// Created by Édouard Gagné on 2020-10-15.
//

#ifndef COMP477PROJECT_RENDERER_H
#define COMP477PROJECT_RENDERER_H

#include "Model.h"
#include "Camera.h"

class Renderer {
    public:
        Renderer(Shader* shader,Camera* camera, std::vector<Model*> models);
        void render();
    private:
        Shader* shader;
        Camera* camera;
        std::vector<Model*> models;
};


#endif //COMP477PROJECT_RENDERER_H
