//
// mapwindow.cpp
// Author: Samuel Vargas 
// Date: 09/20/2019
//

#include "mapwindow.h"

#include <utility>
#include <cassert>
#include "gl_glfw.h"

MapWindow::MapWindow(std::shared_ptr<Gui>  gui) : gui(std::move(gui)) {
}

void MapWindow::render() {
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    ImGui::Begin("Map");
    ImGui::End();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
