//
// main.cpp
// Author: Samuel Vargas
// Date: 08/25/2019
//

#include "gl_glfw.h"
#include "window.h"
#include "raytracer.h"
#include "rgbimage.h"
#include "glfwmanager.h"
#include "gui.h"
#include "arguments.h"
#include "luabinding.h"
#include "filebrowserwindow.h"
#include "fullscreenquad.h"
#include "mapwindow.h"
#include "maprenderer.h"
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
    auto gui = std::make_shared<Gui>(Gui(window.getWindowPointer()));
    std::optional<FileBrowserWindow> fileBrowserWindow = std::nullopt;
    if (args.scriptDirectory != std::nullopt) {
        fileBrowserWindow = FileBrowserWindow(args.scriptDirectory.value(), gui);
    }

    auto mapWindow = MapWindow(gui);

    spdlog::info("Starting Render Loop");

    while (!window.shouldClose()) {
        window.clear();
        glfwPollEvents();

        gui->newFrame();

        if (fileBrowserWindow != std::nullopt) {
            auto selectedPath = fileBrowserWindow->draw();
            if (selectedPath != std::nullopt) {
                const auto universeData = luaBinding.loadUniverseFromScript(selectedPath.value());
                auto rgbImage = RGBImage(1280, 720);
                auto rayTracer = RayTracer(rgbImage, universeData.world, universeData.lightTransport, universeData.eyeMatrix);
                rayTracer.generateImage();
                fullscreenquad.setImage(rgbImage.getRGBData(), rgbImage.getXRes(), rgbImage.getYRes());
            }
        }

        mapWindow.render(window.getWindowPointer());
        fullscreenquad.render(window.getWindowPointer());

        gui->render();
        window.swapBuffers();
        gui->endFrame();
    }

    spdlog::info("Close requested, goodbye!");
    glfwTerminate();
    return 0;
}
