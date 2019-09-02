//
// window.h
// Author: Samuel Vargas
// Date: 08/25/2019
//

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window {
private:
    GLFWwindow *window;
public:
    Window();
    ~Window();
    void clear();
    bool shouldClose();
    GLFWwindow* getWindowPointer();
    void swapBuffers();
    static void onFrameBufferResize(GLFWwindow *window, int x, int y);
};
