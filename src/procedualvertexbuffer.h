//
// procedualvertexbuffer.h
// Author: Samuel Vargas 
// Date: 09/14/2019
//

#pragma once
#include <linalg.h>
#include <vector>
#include <GL/gl.h>

namespace ProcedualVertexBuffer {
    GLvoid* unitWireFrameBuffer(linalg::vec<float, 3> color);
}
