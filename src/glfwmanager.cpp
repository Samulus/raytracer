//
// glfwmanager.cpp
// Author: Samuel Vargas
// Date: 08/25/2019
//

#include "glfwmanager.h"

std::vector<onFrameBufferResizeCallback> GLFWManager::frameBufferCallbacks {};
std::vector<onKeyPressCallback> GLFWManager::keyPressCallbacks {};
std::vector<onErrorCallback> GLFWManager::errorCallbacks {};

void GLFWManager::addFrameBufferResizeCallback(const onFrameBufferResizeCallback& lambda) {
    frameBufferCallbacks.emplace_back(lambda);
}

void GLFWManager::addKeyPressCallback(const onKeyPressCallback &lambda) {
    keyPressCallbacks.emplace_back(lambda);
}

void GLFWManager::addErrorCallback(const onErrorCallback& lambda) {
    errorCallbacks.emplace_back(lambda);
}

// GLFW3 Endpoints
void GLFWManager::onFrameBufferResize(GLFWwindow *window, int x, int y) {
    for (const auto& l : frameBufferCallbacks) {
        l.operator()(window, x, y);
    }
}

void GLFWManager::onKeyPress(GLFWwindow *window, int key, int scancode, int action, int mods) {
    for (const auto& l : keyPressCallbacks) {
        l.operator()(window, key, scancode, action, mods);
    }
}

void GLFWManager::onError(int error, const char* description) {
    for (const auto& l : errorCallbacks) {
        l.operator()(error, description);
    }
}
