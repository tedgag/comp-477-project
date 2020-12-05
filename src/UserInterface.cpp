//
// Created by Édouard on 2020-12-02.
//

#include "UserInterface.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_internal.h>
#include <imgui_impl_opengl3.h>
Scene * UserInterface::currentScene;
Scene * UserInterface::savedScene;
static Scene * savedScene;
void UserInterface::init(GLFWwindow *window, const char* glsl_version, Scene * scene) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    currentScene = scene;
}

void UserInterface::render() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    bool show_demo_window = true;
    //ImGui::ShowDemoWindow(&show_demo_window);

    //ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
    ImGui::SetNextWindowSize(ImVec2(400, 680), 0);
    ImGui::Begin("Controller");                          // Create a window called "Hello, world!" and append into it.
    {
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                    ImGui::GetIO().Framerate);
        ImGui::Text("Particles: %d (Max: %d)", currentScene->nbParticles, currentScene->maxParticles);


        if (currentScene->start) {
            if (currentScene->play) {
                if (ImGui::Button("Stop"))
                    currentScene->play = false;
            } else {
                if (ImGui::Button("Play"))
                    currentScene->play = true;
            }
            ImGui::SameLine();
            if (ImGui::Button("Reset")) {
                currentScene->setFluid();
                currentScene->play = false;
                currentScene->start = false;
                currentScene->setBoundaries(currentScene->initalBoundaries);
            }
        } else {
            if (ImGui::Button("Start")) {
                currentScene->play = true;
                currentScene->start = true;
            }
        }

        if (ImGui::CollapsingHeader("currentScene Options")) {
            float bounds[3] = {currentScene->boundaries.x,
                             currentScene->boundaries.y,
                             currentScene->boundaries.z};
            ImGui::DragFloat3("bounds", bounds,0.02f, 1.0f, 40.0f);
            currentScene->setBoundaries(glm::vec3(bounds[0], bounds[1], bounds[2]));
            float gravity[3] = {currentScene->boundaries.x,
                               currentScene->boundaries.y,
                               currentScene->boundaries.z};
            ImGui::DragFloat3("gravity", gravity,0.02f, -20.0f, 20.0f);

        }
        if (ImGui::CollapsingHeader("Fluid Options")) {
            int dimensions[3] = {(int)currentScene->fluidDimensions.x,
                                 (int)currentScene->fluidDimensions.y,
                                 (int)currentScene->fluidDimensions.z};
            float pos[3] = {currentScene->fluidPosition.x, currentScene->fluidPosition.y, currentScene->fluidPosition.z};
            float col[3] = {currentScene->particleColor.x, currentScene->particleColor.y,currentScene->particleColor.z};

            ImGui::DragFloat3("position", pos, 0.01f, 0.0f, 40.0f);
            ImGui::SliderInt3("dimensions", dimensions, 2, 40);
            ImGui::ColorEdit3("color", col);


            currentScene->setFluid(glm::vec3(pos[0], pos[1], pos[2]),glm::vec3(dimensions[0], dimensions[1], dimensions[2]));
            currentScene->particleColor = glm::vec3(col[0],col[1],col[2]);
        }
        if (ImGui::CollapsingHeader("Camera Controls")) {
            ImGui::Text("F: Enable/Disable Free Camera Mode");
            ImGui::Text("WASD: Move Around in Direction of Cursor");
            ImGui::Text("SHIFT (Hold): Move Slightly Faster");
        }
        // Buttons return true when clicked (most widgets return true when edited/activated)
    }
    ImGui::End();

    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

