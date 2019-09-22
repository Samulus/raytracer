//
// gui.h
// Author: Samuel Vargas 
// Date: 09/11/2019
//

#pragma once
#include "gl_glfw.h"
#include <imgui.h>
#include <vector>
#include <string>

class Gui {
private:
    ImGuiIO io;
public:
    explicit Gui(GLFWwindow* window);
    void newFrame();
    void render();
    void endFrame();
};
