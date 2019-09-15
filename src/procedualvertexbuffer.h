//
// procedualvertexbuffer.h
// Author: Samuel Vargas 
// Date: 09/14/2019
//

#pragma once
#include <vector>
#include <GL/gl.h>

class ProcedualVertexBuffer {
private:
    std::vector<GLvoid> buffer;
public:
    ProcedualVertexBuffer();

    //ProcedualVertexBuffer&& addLine();
};
