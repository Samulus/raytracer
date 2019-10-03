//
// mapwindow.cpp
// Author: Samuel Vargas 
// Date: 09/20/2019
//

#include "mapwindow.h"

#include <utility>
#include "gl_glfw.h"

MapWindow::MapWindow(std::shared_ptr<Gui>  gui) : mapRenderer(MapRenderer()), gui(std::move(gui)) {
}

void MapWindow::render(GLFWwindow* window) {
    mapRenderer.render();

    ImGui::Begin("Map");

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    ImGui::GetWindowDrawList()->AddImage(
            reinterpret_cast<ImTextureID>(mapRenderer.getFramebufferTextureId()),
            ImVec2(ImGui::GetCursorScreenPos()),
            ImVec2(ImGui::GetCursorScreenPos().x + width/2,
                   ImGui::GetCursorScreenPos().y + height/2), ImVec2(0, 1), ImVec2(1, 0));


    ImGui::End();
}