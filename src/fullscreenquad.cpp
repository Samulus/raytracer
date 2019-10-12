//
// fullscreenquad.cpp
// Author: Samuel Vargas 
// Date: 09/21/2019
//
// TODO:
//  - Do not regenerate textureIds if overwriting…

#include <cassert>
#include <stdexcept>

#include "fullscreenquad.h"

const char *RAYTRACER_FRAGMENT_SHADER =
#include "raytracer.frag"
;

const char *RAYTRACER_VERTEX_SHADER =
#include "raytracer.vert"
;

FullscreenQuad::FullscreenQuad() : shader(Shader(RAYTRACER_VERTEX_SHADER, RAYTRACER_FRAGMENT_SHADER)) {
    if (!shader.cacheUniformLocation("iResolution")) {
        throw std::runtime_error("Could not find uniform `iResolution`");
    }

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, quadVertices.size() * sizeof(GLfloat), &quadVertices.front(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, quadIndices.size() * sizeof(GLuint), &quadIndices.front(), GL_STATIC_DRAW);

    glUseProgram(shader.getProgramID());
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, nullptr);
}

void FullscreenQuad::setImage(const std::vector<GLubyte>& imageData, GLuint xRes, GLuint yRes) {
    glBindVertexArray(vao);

    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D, 0,
                 GL_RGB, xRes, yRes,
                 0, GL_RGB, GL_UNSIGNED_BYTE, &imageData.front());
    glGenerateMipmap(GL_TEXTURE_2D);

    // Setup Texture Parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    float borderColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Upload Texture Coordinates
    glGenBuffers(1, &textureCoordinateBuffer);
    glBindBuffer(GL_TEXTURE_BUFFER, textureCoordinateBuffer);
    glBufferData(GL_TEXTURE_BUFFER, texCoords.size() * sizeof(GLfloat), &texCoords.front(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, nullptr);
    assert(glGetError() == GL_NO_ERROR);
}

void FullscreenQuad::resize(GLuint xRes, GLuint yRes) {
    glUseProgram(shader.getProgramID());
    const auto& uniformLocation = shader.getUniformLocation("iResolution");
    if (uniformLocation < 0) {
        throw std::runtime_error("Missing uniform `iResolution`");
    }
    glUniform2f(uniformLocation, float(xRes), float(yRes));
}

void FullscreenQuad::render(GLFWwindow* window) {
    glBindVertexArray(vao);
    glUseProgram(shader.getProgramID());
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}
