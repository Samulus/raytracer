//
// maprenderer.h
// Author: Samuel Vargas 
// Date: 09/21/2019
// Description: Creates the framebuffer for rendering a small preview of the
//              world into a framebufferColorTextureId (for later embedding in an ImGui Window).
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
    GLuint framebufferId = 0;
    GLuint framebufferColorTextureId = 0;
    GLuint renderBufferId = 0;

    // Map Vertex Data (GL_LINES)
    GLuint vertexArrayId;
    GLuint wireframeVertexBufferId;

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

    // Texture Data
    std::vector<GLfloat> texCoords {0, 0, 1, 0, 0, 1, 1, 1};
    GLuint textureBufferId = 0;

    // Shading
    Shader shader;

public:
    explicit MapRenderer();
    void render();
    GLuint getFramebufferTextureId();
private:
    void initFrameBuffer();
};
