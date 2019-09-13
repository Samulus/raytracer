//
// gui.h
// Author: Samuel Vargas 
// Date: 09/11/2019
//

#pragma once
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"

class Gui {
public:
    explicit Gui(GLFWwindow* window);
};
