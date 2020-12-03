//
// Created by Édouard on 2020-12-02.
//

#include "UserInterface.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_internal.h>
#include <imgui_impl_opengl3.h>

void UserInterface::init(GLFWwindow *window, const char* glsl_version) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

void UserInterface::render(Simulation *simulation) {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    bool show_demo_window = true;
    ImGui::ShowDemoWindow(&show_demo_window);



    //ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
    ImGui::SetNextWindowSize(ImVec2(400, 680), 0);
    ImGui::Begin("Controller");                          // Create a window called "Hello, world!" and append into it.
    {
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                    ImGui::GetIO().Framerate);
        ImGui::Text("Particles: %d (Max: %d)", simulation->nbParticles, simulation->maxParticles);


        if (simulation->start) {
            if (simulation->play) {
                if (ImGui::Button("Stop"))
                    simulation->play = false;
            } else {
                if (ImGui::Button("Play"))
                    simulation->play = true;
            }
            ImGui::SameLine();
            if (ImGui::Button("Reset")) {
                simulation->setFluid();
                simulation->play = false;
                simulation->start = false;
            }
        } else {
            if (ImGui::Button("Start")) {
                simulation->play = true;
                simulation->start = true;
            }
        }

        if (ImGui::CollapsingHeader("Scene Options")) {
            int bounds[3] = {(int)simulation->gridDimensions.x,
                             (int)simulation->gridDimensions.y,
                             (int)simulation->gridDimensions.z};
            ImGui::SliderInt3("bounds", bounds, 1, 40);
            simulation->setBoundaries(glm::vec3(bounds[0], bounds[1], bounds[2]));
        }
        if (ImGui::CollapsingHeader("Fluid Options")) {
            int dimensions[3] = {(int)simulation->fluidDimensions.x,
                                 (int)simulation->fluidDimensions.y,
                                 (int)simulation->fluidDimensions.z};
            float pos[3] = {simulation->fluidPosition.x, simulation->fluidPosition.y, simulation->fluidPosition.z};
            float col[3] = {simulation->particleColor.x, simulation->particleColor.y,simulation->particleColor.z};

            ImGui::DragFloat3("position", pos, 0.01f, 0.0f, 40.0f);
            ImGui::SliderInt3("dimensions", dimensions, 2, 40);
            ImGui::ColorEdit3("color", col);


            simulation->setFluid(glm::vec3(pos[0], pos[1], pos[2]),glm::vec3(dimensions[0], dimensions[1], dimensions[2]));
            simulation->particleColor = glm::vec3(col[0],col[1],col[2]);
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

