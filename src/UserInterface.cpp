//
// Created by Édouard on 2020-12-02.
//

#include "UserInterface.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_internal.h>
#include <imgui_impl_opengl3.h>
#include <iostream>

float averageFrameRate = 0;
float averageTime = 0;
float totalFrameRate = 0;
float totalTime = 0;
float frameCount = 0;
void UserInterface::init(GLFWwindow *window, const char* glsl_version) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

void UserInterface::render(const std::shared_ptr<Scene> & scene) {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    bool show_demo_window = true;
    float currentFrameRate = ImGui::GetIO().Framerate;
    float currentTime = 1000.0f / currentFrameRate;
    ImGui::ShowDemoWindow(&show_demo_window);
    ImGui::SetNextWindowSize(ImVec2(400, 680), 0);
    ImGui::Begin("Controller");                          // Create a window called "Hello, world!" and append into it.
    {
        ImGui::Text("Current: %.3f ms/frame (%.1f FPS)", currentTime,currentFrameRate);
        ImGui::Text("Last: %.3f ms/frame (%.1f FPS)", averageTime,averageFrameRate);
        ImGui::Text("Particles: %d (Max: %d)", scene->nbParticles, scene->maxParticles);

        if (scene->start) {
            if (scene->play) {
                frameCount ++;
                totalFrameRate += currentFrameRate;
                totalTime += currentTime;
                if (ImGui::Button("Stop"))
                    scene->play = false;
            } else {
                if (ImGui::Button("Play"))
                    scene->play = true;
            }
            ImGui::SameLine();
            if (ImGui::Button("Reset")) {
                averageFrameRate = totalFrameRate / frameCount;
                averageTime = totalTime / frameCount;
                scene->reset();
            }
        } else {
            if (ImGui::Button("Start")) {
                scene->save();
                averageFrameRate = 0;
                averageTime = 0;
                frameCount = 0;
            }
        }

        if (ImGui::CollapsingHeader("Scene Options", ImGuiTreeNodeFlags_DefaultOpen)) {
            float bounds[3] = {scene->boundaries.x,
                               scene->boundaries.y,
                               scene->boundaries.z};
            ImGui::DragFloat3("bounds", bounds,0.02f, 1.0f, 40.0f);
            scene->setBoundaries(glm::vec3(bounds[0], bounds[1], bounds[2]));
            float gravity[3] = {scene->gravity.x,
                                scene->gravity.y,
                                scene->gravity.z};
            ImGui::DragFloat3("gravity", gravity,0.02f, -20.0f, 20.0f);
            scene->setGravity(glm::vec3(gravity[0],gravity[1],gravity[2]));
            bool enableSkybox = scene->enableSkybox;
            bool enableBounds = scene->enableBounds;
            ImGui::Checkbox("Enable Skybox", &enableSkybox); ImGui::SameLine();
            ImGui::Checkbox("Enable Boundaries", &enableBounds);
            scene->setSkybox(enableSkybox);
            scene->setBounds(enableBounds);
        }
        if (ImGui::CollapsingHeader("Fluid Options", ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::Text("h: %.1f", scene->simulation->h); ImGui::SameLine();
            ImGui::Text("  particle radius: %.1f", scene->simulation->particleRadius);
            int dimensions[3] = {(int)scene->fluidDimensions.x,
                                 (int)scene->fluidDimensions.y,
                                 (int)scene->fluidDimensions.z};
            float pos[3] = {scene->fluidPosition.x, scene->fluidPosition.y, scene->fluidPosition.z};
            float col[3] = {scene->particleColor.x, scene->particleColor.y,scene->particleColor.z};

            ImGui::DragFloat3("position", pos, 0.01f, 0.0f, 40.0f);
            ImGui::SliderInt3("dimensions", dimensions, 2, 40);
            ImGui::ColorEdit3("color", col);
            float viscosity = scene->viscosity;
            ImGui::DragFloat("viscosity", &viscosity,0.02f, 0.0f, 80.0f);
            scene->setViscosity(viscosity);
            float particleMass = scene->particleMass;
            ImGui::DragFloat("mass", &particleMass,0.02f, 20.0f, 160.0f);
            scene->setMass(particleMass);
            scene->setFluid(glm::vec3(pos[0], pos[1], pos[2]),glm::vec3(dimensions[0], dimensions[1], dimensions[2]));
            scene->setColor(glm::vec3(col[0],col[1],col[2]));
        }

        if (ImGui::CollapsingHeader("Controls",ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::Text("CTRL + Click: directly input a value");
            ImGui::Text("F: enable/disable Free Camera Mode");
            ImGui::Text("WASD: move around in direction of cursor");
            ImGui::Text("SHIFT (hold): move slightly faster");
            ImGui::Text("ESC: close the program");
        }
        // Buttons return true when clicked (most widgets return true when edited/activated)
    }
    ImGui::End();

    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

