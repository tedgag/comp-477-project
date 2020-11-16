
#include <stdio.h>

#include "helpers/IncludeHeader.h"

#include "Simulation.h"
#include "EventHandler.h"

using namespace glm;

int main(){
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Open a window and create its OpenGL context
    GLFWwindow* window; // (In the accompanying source code, this variable is global)
    window = glfwCreateWindow( SCR_WIDTH, SCR_HEIGHT, "Test", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental=true; // Needed in core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.5f, 0.5f, 1.0f);


    auto * camera = new Camera(glm::vec3(0.0f, 6.0f, 6.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
    auto * sim = new Simulation(camera);
    EventHandler::init(window, camera);
    // Main loop
    float lastFrame = 0.0f;
    float deltaTime = 0.0f;

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        EventHandler::processInput(window, deltaTime);
        sim->run();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

