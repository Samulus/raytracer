//
// glfwmanager.h
// Author: Samuel Vargas
// Date: 08/25/2019
//

#pragma once
#include <vector>
#include <functional>
#include <GLFW/glfw3.h>

using onFrameBufferResizeCallback = std::function<void(GLFWwindow* window, int x, int y)>;
using onKeyPressCallback = std::function<void(GLFWwindow* window, int key, int scancode, int action, int mods)>;
using onErrorCallback = std::function<void(int error, const char* description)>;

class GLFWManager {
private:
    static std::vector<onFrameBufferResizeCallback> frameBufferCallbacks;
    static std::vector<onKeyPressCallback> keyPressCallbacks;
    static std::vector<onErrorCallback> errorCallbacks;
public:
    GLFWManager() = delete;
    static void addFrameBufferResizeCallback(const onFrameBufferResizeCallback& lambda);
    static void addKeyPressCallback(const onKeyPressCallback& lambda);
    static void addErrorCallback(const onErrorCallback& lambda);

    static void onFrameBufferResize(GLFWwindow* window, int x, int y);
    static void onKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void onError(int error, const char* description);
};
