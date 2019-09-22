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
    glGenFramebuffers(1, &fboId);
    glBindFramebuffer(GL_FRAMEBUFFER, (GLuint)fboId);

    // Color Buffer
    glGenTextures(1, &colorTextureId);
    glBindTexture(GL_TEXTURE_2D, colorTextureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 512, 512, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, colorTextureId, 0);

    // Attach depthStencil
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 512, 512);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    auto framebufferStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    assert(framebufferStatus == GL_FRAMEBUFFER_COMPLETE);

    glGenVertexArrays(1, &vaoId);
    glGenBuffers(1, &vboId);
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER,
            wireframeLines.size() * sizeof(GLfloat),
            &wireframeLines.front(),
            GL_STATIC_DRAW);
    assert(glGetError() == GL_NO_ERROR);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void MapRenderer::render() {
    glBindFramebuffer(GL_FRAMEBUFFER, fboId);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    //glBindTexture(GL_TEXTURE_2D, texId);

    glBindVertexArray(vaoId);
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glUseProgram(shader.getProgramID());
    glViewport(0, 0, 512, 512);
    glDrawArrays(GL_LINES, 0, wireframeLines.size() / 3);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

