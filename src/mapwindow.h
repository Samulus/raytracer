//
// mapwindow.h
// Author: Samuel Vargas 
// Date: 09/20/2019
//

#pragma once
#include <memory>
#include "gui.h"
#include "maprenderer.h"

class MapWindow {
    MapRenderer mapRenderer;
    unsigned int fbo = 0;
    unsigned int mapTextureId = 0;
    std::shared_ptr<Gui> gui;
public:
    explicit MapWindow(std::shared_ptr<Gui> gui);
    void render(GLFWwindow* window);
};
