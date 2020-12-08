
#include <stdio.h>
#include <iostream>

#include <memory>

#include "helpers/IncludeHeader.h"

#include "Scene.h"
#include "EventHandler.h"
#include "UserInterface.h"

using namespace glm;

int main(){
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        return -1;
    }
    const char* glsl_version = "#version 330";
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


    GLFWwindow* window;
    window = glfwCreateWindow( SCR_WIDTH, SCR_HEIGHT, "COMP-477", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window.\n" );
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);


    glewExperimental=true;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW.\n");
        return -1;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    std::shared_ptr<Camera> camera = std::make_shared<Camera>(
            glm::vec3(-15.0f, 10.0f, 6.0f),
            glm::vec3(0.0f, 1.0f, 0.0f),
            0.0f,
            -15.0f);
    std::shared_ptr<Scene> scene =  std::make_shared<Scene>(camera);
    UserInterface::init(window, glsl_version);
    EventHandler::init(window, camera, scene);

    // Main loop
    float lastFrame = 0.0f;
    float deltaTime = 0.0f;

    while (!glfwWindowShouldClose(window)) {

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        EventHandler::processInput(window, deltaTime);
        scene->render(deltaTime);
        if (scene->showMenu) {
            UserInterface::render(scene, deltaTime);
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

