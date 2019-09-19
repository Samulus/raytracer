//
// rgbimage.cpp
// Author: Samuel Vargas
// Date: 08/25/2019
//

#include "rgbimage.h"
#include <parallel/algorithm>
RGBImage::RGBImage(unsigned int xRes, unsigned int yRes) : xRes(xRes), yRes(yRes) {
    byteData = std::vector<GLubyte>(xRes * yRes * 3, 0);
}

RGBImage::~RGBImage() = default;

const std::vector<GLubyte>& RGBImage::getRGBData() {
    return byteData;
}

const GLvoid *RGBImage::getRGBDataPointer() {
    return &byteData.front();
}

unsigned int RGBImage::getXRes() {
    return xRes;
}

unsigned int RGBImage::getYRes() {
    return yRes;
}

void RGBImage::forEachPixel(
        const std::function<void(GLubyte& r, GLubyte& g, GLubyte& b, unsigned int x, unsigned int y)> &lambda) {
    for (unsigned int i=0; i < xRes * yRes * 3; i += 3) {
        auto x = (i / 3) % xRes;
        auto y = (i / 3) / xRes;
        lambda.operator()(byteData[i], byteData[i + 1], byteData[i + 2], x, y);
    }
}
