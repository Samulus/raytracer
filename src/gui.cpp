//
// gui.cpp
// Author: Samuel Vargas 
// Date: 09/11/2019
//

#include "gui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

Gui::Gui(GLFWwindow* window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    io = ImGui::GetIO();
}

void Gui::newFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Gui::render() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Gui::endFrame() {
    ImGui::EndFrame();
}
