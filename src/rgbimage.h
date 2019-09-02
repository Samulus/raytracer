//
// rgbimage.h
// Author: Samuel Vargas 
// Date: 08/25/2019
//

#pragma once
#include <GL/glew.h>
#include <vector>
#include <functional>
#include <iterator>

struct RGBPixel {
    GLubyte r;
    GLubyte g;
    GLubyte b;
};

class RGBImage {
private:
    unsigned int xRes;
    unsigned int yRes;
    std::vector<GLubyte> byteData;
public:
    RGBImage(unsigned int xRes, unsigned int yRes);
    const std::vector<GLubyte>& getRGBData();
    const GLvoid* getRGBDataPointer();
    unsigned int getXRes();
    unsigned int getYRes();
    void forEachPixel(const std::function<void(GLubyte& r, GLubyte& g, GLubyte& b, unsigned int x, unsigned int y)>& lambda);
};

