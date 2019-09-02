//
// window.cpp
// Author: Samuel Vargas
// Date: 08/25/2019
//


#include <iostream>
#include "window.h"

Window::Window() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    // Init GLFW3
    window = glfwCreateWindow(1280, 720, "raytracer", nullptr, nullptr);
    if (window == nullptr) {
        throw std::runtime_error("Unable to init Window.");
    }
    glfwMakeContextCurrent(window);

    // Init GLEW
    if (glewInit() != GLEW_OK ){
        throw std::runtime_error("Unable to init GLEW");
    }

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glClearColor(1, 1, 1, 1);
}

Window::~Window() {
    glfwDestroyWindow(window);
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(window) == GLFW_TRUE;
}

void Window::clear() {
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

GLFWwindow *Window::getWindowPointer() {
    return window;
}

void Window::swapBuffers() {
    glfwSwapBuffers(window);
}

// GLFW Callbacks
void Window::onFrameBufferResize(GLFWwindow* window, int x, int y) {
    glViewport(0, 0, x, y);
}
