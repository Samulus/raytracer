//
// fullscreenquad.h
// Author: Samuel Vargas 
// Date: 09/21/2019
//

#pragma once
#include "gl_glfw.h"
#include "shader.h"
#include <vector>

class FullscreenQuad {
private:
    GLuint vao = 0;
    GLuint vbo = 0;
    GLuint ebo = 0;
    GLuint textureId;
    GLuint textureCoordinateBuffer;
    std::vector<GLfloat> quadVertices {1.0, 1.0, -1.0, 1.0, -1.0, -1.0, 1.0, -1.0};
    std::vector<GLuint> quadIndices = std::vector<GLuint> { 0, 3, 2, 2, 1, 0};
    std::vector<GLfloat> texCoords {0, 0, 1, 0, 0, 1, 1, 1};
    Shader shader;
public:
    explicit FullscreenQuad();
    void setImage(const std::vector<GLubyte>& imageData, GLuint xRes, GLuint yRes);
    void resize(GLuint xRes, GLuint yRes);
    void render(GLFWwindow* window);
};

