//
// main.cpp
// Author: Samuel Vargas
// Date: 08/25/2019
//

#include "window.h"
#include "shader.h"
#include "raytracer.h"
#include "world.h"
#include "rgbimage.h"
#include "glfwmanager.h"
#include "diffuselighting.h"
#include "scenes.h"
#include "gui.h"
#include "arguments.h"
#include "luabinding.h"
#include "filebrowserwindow.h"

#include <optional>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

const char *RAYCASTER_FRAGMENT_SHADER =
#include "raycaster.frag"
;

const char *RAYCASTER_VERTEX_SHADER =
#include "raycaster.vert"
;

const char *DEFAULT_LUA_SCENE =
#include "defaultscene.lua"
;

GLuint setupVertexArrayObject();
Shader setupShader();
void setupTexture(RGBImage& image);

int main(int ac, char **av) {
    const auto args = Arguments::handleArguments(ac, av);

    if (!glfwInit()) {
        spdlog::critical("Unable to initialize GLFW3!");
        return 1;
    } else {
        spdlog::info("Displaying default scene");
    }

    spdlog::info("Initializing world from Lua scene file.");

    auto luaBinding = LuaBinding();
    auto world = World();

    std::unique_ptr<WorldLightEyeTuple> worldLightEyeTuple = nullptr;
    if (args.scriptDirectory != std::nullopt) {
        spdlog::info("scriptDirectory set to: {}", args.scriptDirectory.value().string());
        worldLightEyeTuple = nullptr; // NOOP for now;
    } else {
        spdlog::info("scriptDirectory not specified, using default scene");
        worldLightEyeTuple = luaBinding.loadWorldFromScript(DEFAULT_LUA_SCENE);
    }

    spdlog::info("World initialized");

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

    auto vao = setupVertexArrayObject();
    spdlog::info("VAO initialized");

    auto shader = setupShader();
    spdlog::info("Shader initialized");

    const auto& onResize = [&](GLFWwindow* window, int x, int y) {
        glViewport(0, 0, x, y);
        const auto& uniformLocation = shader.getUniformLocation("iResolution");
        if (uniformLocation < 0) {
            spdlog::critical("Missing iResolution uniform, bailing…");
            exit(1);
        }

        glUniform2f(uniformLocation, float(x), float(y));
    };
    GLFWManager::addFrameBufferResizeCallback(onResize);


    glfwSetFramebufferSizeCallback(window.getWindowPointer(), GLFWManager::onFrameBufferResize);
    spdlog::info("Framebuffer Resize  Callback initialized");

    auto lightTransportAlgorithm = DiffuseLighting();
    Scene::ballsHoveringAboveGlobe(world, lightTransportAlgorithm);

    auto rgbImage = RGBImage(1280, 720);
    auto rayTracer = RayTracer(rgbImage, world, lightTransportAlgorithm);
    rayTracer.generateImage();
    spdlog::info("Image RayTraced / initialized");

    glBindVertexArray(vao);
    setupTexture(rgbImage);
    spdlog::info("Texture initialized");

    spdlog::info("Setup Viewport");

    // setup the viewport initially
    int width, height;
    glfwGetFramebufferSize(window.getWindowPointer(), &width, &height);
    onResize(window.getWindowPointer(), width, height);

    // UI
    auto gui = std::make_shared<Gui>(Gui(window.getWindowPointer()));

    std::optional<FileBrowserWindow> fileBrowserWindow = std::nullopt;
    if (args.scriptDirectory != std::nullopt) {
        fileBrowserWindow = FileBrowserWindow(args.scriptDirectory.value(), gui);
    }

    spdlog::info("Starting Render Loop");
    while (!window.shouldClose()) {
        window.clear();
        glfwPollEvents();

        gui->newFrame();

        if (fileBrowserWindow != std::nullopt) {
            fileBrowserWindow->draw();
        }

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        gui->render();
        window.swapBuffers();
        gui->endFrame();
    }

    spdlog::info("Close requested, goodbye!");
    glfwTerminate();
    return 0;
}

/**
 * Setup a VAO for a fullscreen quad
 * (so that we can apply the raytraced image as a texture to the quad)
 */

GLuint setupVertexArrayObject() {
    auto fullScreenQuadData = std::vector<GLfloat> {
        1.0, 1.0,
        -1.0, 1.0,
        -1.0, -1.0,
        1.0, -1.0
    };

    auto fullScreenQuadIndexData = std::vector<GLuint> {
        0, 3, 2,
        2, 1, 0
    };

    GLuint vertexArrayObjectId, vertexBufferId, indexBufferId;
    glGenVertexArrays(1, &vertexArrayObjectId);
    glGenBuffers(1, &vertexBufferId);
    glGenBuffers(1, &indexBufferId);
    glBindVertexArray(vertexArrayObjectId);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER,
                 fullScreenQuadData.size() * sizeof(GLfloat),
                 &fullScreenQuadData.front(),
                 GL_STATIC_DRAW
    );
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 fullScreenQuadIndexData.size() * sizeof(GLuint),
                 &fullScreenQuadIndexData.front(),
                 GL_STATIC_DRAW
    );

    glEnableVertexAttribArray(0); // 'in vec2 aPos'
    glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, nullptr);
    return vertexArrayObjectId;
}

Shader setupShader() {
    auto shader = Shader(RAYCASTER_VERTEX_SHADER, RAYCASTER_FRAGMENT_SHADER);
    glUseProgram(shader.getProgramID());
    if (!shader.rememberUniformLocation("iResolution")) {
        spdlog::critical("Could not find iResolution uniform in raytracer.vert. Bailing!");
        exit(1);
    }

    return shader;
}

void setupTexture(RGBImage& image) {

    // Upload Image
    glActiveTexture(GL_TEXTURE0);
    GLuint textureId = 0;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D, 0,
            GL_RGB, image.getXRes(), image.getYRes(),
            0, GL_RGB, GL_UNSIGNED_BYTE, image.getRGBDataPointer());
    glGenerateMipmap(GL_TEXTURE_2D);

    // Setup Texture Parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    float borderColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Upload Texture Coordinates
    GLuint textureCoordinateBuffer;
    auto texCoords = std::vector<GLfloat>{
        0, 0,
        1, 0,
        0, 1,
        1, 1
    };
    glGenBuffers(1, &textureCoordinateBuffer);
    glBindBuffer(GL_TEXTURE_BUFFER, textureCoordinateBuffer);
    glBufferData(GL_TEXTURE_BUFFER,
            texCoords.size() * sizeof(GLfloat),
            &texCoords.front(),
            GL_STATIC_DRAW);

    glEnableVertexAttribArray(1); // 'in vec2 aTexCoord'
    glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, nullptr);
}
