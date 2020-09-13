//
// main.cpp
// Author: Samuel Vargas
// Date: 08/25/2019
//

#include "gl_glfw.h"
#include "window.h"
#include "raytracer.h"
#include "rgbimage.h"
#include "rgbimagethreaded.h"
#include "glfwmanager.h"
#include "arguments.h"
#include "luabinding.h"
#include "fullscreenquad.h"
#include <optional>
#include <spdlog/spdlog.h>

int main(int ac, char **av) {
    const auto args = Arguments::handleArguments(ac, av);

    if (!glfwInit()) {
        spdlog::critical("Unable to initialize GLFW3!");
        return 1;
    }

    auto luaBinding = LuaBinding();
    auto window = Window();

    spdlog::info("Window initialized");

    GLFWManager::addErrorCallback([] (int error, const char* description){
        spdlog::critical(std::string(description));
        exit(1);
    });

    GLFWManager::addKeyPressCallback([] (GLFWwindow* window, int key, int scancode, int action, int mods){
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
    });

    glfwSetKeyCallback(window.getWindowPointer(), GLFWManager::onKeyPress);
    glfwSetErrorCallback(GLFWManager::onError);
    spdlog::info("Keyboard / Error Callback initialized");

    auto fullscreenquad = FullscreenQuad();
    const auto& onResize = [&](GLFWwindow* window, int x, int y) {
        fullscreenquad.resize(x, y);
    };

    GLFWManager::addFrameBufferResizeCallback(onResize);
    glfwSetFramebufferSizeCallback(window.getWindowPointer(), GLFWManager::onFrameBufferResize);
    spdlog::info("FullscreenQuad initialized");

    int width, height;
    glfwGetFramebufferSize(window.getWindowPointer(), &width, &height);
    onResize(window.getWindowPointer(), width, height);

    // UI
    spdlog::info("Starting Render Loop");

    const auto universeData = luaBinding.loadUniverseFromScript("../scenes/RGB.lua");
    RGBImage rgbImage(1280, 720);
    RayTracer rt(rgbImage, universeData.world, universeData.lightTransport, universeData.eyeMatrix);
    rt.generateImage();
    fullscreenquad.setImage(rgbImage.getRGBData(), rgbImage.getXRes(), rgbImage.getYRes());

    while (!window.shouldClose()) {
        window.clear();
        glfwPollEvents();
        fullscreenquad.render(window.getWindowPointer());
        window.swapBuffers();
    }

    spdlog::info("Close requested, goodbye!");
    glfwTerminate();
    exit(0);
}
