//
// maprenderer.cpp
// Author: Samuel Vargas 
// Date: 09/21/2019
//
// TODO:
//   - Clean up the framebuffer (glDeleteFrameBuffers(…)) when we're done with it.
//   - Use glViewport(…) when rendering to support mismatched fbo / default fbo reses

const char *MAP_FRAGMENT_SHADER =
#include "map.frag"
;

const char *MAP_VERTEX_SHADER =
#include "map.vert"
;

#include "maprenderer.h"
#include <cassert>

MapRenderer::MapRenderer() : shader(Shader(MAP_VERTEX_SHADER, MAP_FRAGMENT_SHADER)) {
    initFrameBuffer();

}

void MapRenderer::initFrameBuffer() {
    glGenFramebuffers(1, &framebufferId);
    glGenTextures(1, &framebufferColorTextureId);
    glGenRenderbuffers(1, &renderBufferId);

    glBindFramebuffer(GL_FRAMEBUFFER, (GLuint)framebufferId);
    glBindTexture(GL_TEXTURE_2D, framebufferColorTextureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 512, 512, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, framebufferColorTextureId, 0);

    // Attach depthStencil
    glBindRenderbuffer(GL_RENDERBUFFER, renderBufferId);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 512, 512);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBufferId);

    // Setup drawbuffers
    GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

    auto framebufferStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    assert(framebufferStatus == GL_FRAMEBUFFER_COMPLETE);

    glGenVertexArrays(1, &vertexArrayId);
    glGenBuffers(1, &wireframeVertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, wireframeVertexBufferId);
    glBufferData(GL_ARRAY_BUFFER,
                 wireframeLines.size() * sizeof(GLfloat),
                 &wireframeLines.front(),
                 GL_STATIC_DRAW);
    assert(glGetError() == GL_NO_ERROR);

    // Coordinates for texture

    glGenBuffers(1, &textureBufferId);
    glBindBuffer(GL_TEXTURE_BUFFER, textureBufferId);
    glBufferData(GL_TEXTURE_BUFFER,
                 texCoords.size() * sizeof(GLfloat),
                 &texCoords.front(),
                 GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, 0, nullptr);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void MapRenderer::render() {
    glBindVertexArray(vertexArrayId);
    glUseProgram(shader.getProgramID());
    glBindFramebuffer(GL_FRAMEBUFFER, framebufferId);

    glClearColor(0.5, 0.5, 0.5, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glLineWidth(10);
    //glBindTexture(GL_TEXTURE_2D, texId);

    glBindVertexArray(vertexArrayId);
    glBindBuffer(GL_ARRAY_BUFFER, wireframeVertexBufferId);
    glUseProgram(shader.getProgramID());
    glViewport(0, 0, 512, 512);
    glDrawArrays(GL_LINES, 0, 8);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glUseProgram(0);
}

GLuint MapRenderer::getFramebufferTextureId() {
    return framebufferColorTextureId;
}


