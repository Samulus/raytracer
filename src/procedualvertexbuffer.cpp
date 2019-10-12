//
// procedualvertexbuffer.cpp
// Author: Samuel Vargas 
// Date: 09/14/2019
//

#include "procedualvertexbuffer.h"
#include <vector>

GLvoid* ProcedualVertexBuffer::unitWireFrameBuffer(linalg::vec<float, 3> color) {

    std::vector<GLfloat> vertices = {
        // Rear
        -0.5,  0.5, -0.5, // upper rear left vertex
         0.5,  0.5, -0.5, // upper rear right vertex
        -0.5, -0.5, -0.5, // bottom rear left vertex
         0.5, -0.5, -0.5  // bottom rear right vertex
        // Front
        -0.5,  0.5,  0.5, // upper front left vertex
         0.5,  0.5,  0.5, // upper front right vertex
        -0.5, -0.5,  0.5, // bottom front left vertex
         0.5, -0.5,  0.5  // bottom front right vertex
    };

    std::vector<GLuint> indices = {

    };

    return nullptr;
}
