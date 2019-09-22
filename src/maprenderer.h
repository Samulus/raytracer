//
// maprenderer.h
// Author: Samuel Vargas 
// Date: 09/21/2019
// Description: Creates the framebuffer for rendering a small preview of the
//              world into a colorTextureId (for later embedding in an ImGui Window).
//              Should help simplify problems like "why can't I see anything
//              with my current scene file?)


#pragma once
#include "gl_glfw.h"
#include "shader.h"
#include "world.h"
#include <vector>

class MapRenderer {
    //std::shared_ptr<UniverseData> world;

    // FBO Data
    GLuint fboId = 0;
    GLuint texId = 0;
    GLuint colorTextureId = 0;
    GLuint rbo = 0;

    // Map Vertex Data (GL_LINES)
    GLuint vaoId;
    GLuint vboId;

    std::vector<GLfloat> wireframeLines = {
        -0.5, 0.5, -0.5,  0.5 , 0.5 -0.5,  // Rear Top
        -0.5, -0.5, -0.5, 0.5, -0.5, -0.5, // Rear Bottom
        -0.5, 0.5, -0.5, -0.5, -0.5, -0.5, // Rear Left
        0.5, 0.5, -0.5,   0.5, -0.5, -0.5  // Rear Right

        -0.5, 0.5, 0.5,  0.5 , 0.5, 0.5, // Front Top
        -0.5, -0.5, 0.5, 0.5, -0.5, 0.5, // Front Bottom
        -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, // Front Left
        0.5, 0.5, 0.5,   0.5, -0.5, 0.5  // Front Right

        -0.5, 0.5, -0.5, -0.5, 0.5, 0.5,   // Left Top
        -0.5, -0.5, -0.5, -0.5, -0.5, 0.5, // Left Bottom
        0.5, 0.5, -0.5, 0.5, 0.5, 0.5,     // Right Top
        0.5, -0.5, -0.5, 0.5, -0.5, 0.5    // Right Bottom


    };

    // Shading
    Shader shader;

public:
    explicit MapRenderer();

    void render();
};
