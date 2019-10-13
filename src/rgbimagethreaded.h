//
// rgbimagethreaded.h
// Author: Samuel Vargas
// Date: 10/12/2019
//

#pragma once
#include "gl_glfw.h"
#include <vector>
#include <functional>
#include <stdexcept>
#include <mutex>

class RGBImageThreaded {
    unsigned int xRes;
    unsigned int yRes;
    std::mutex lock;
    std::vector<GLubyte> byteData;
    std::vector<std::thread> threads;
public:
    RGBImageThreaded(unsigned int numberThreads, unsigned int xRes, unsigned int yRes);
    ~RGBImageThreaded();
    const std::vector<GLubyte>& getPixelData();
    unsigned int getXRes();
    unsigned int getYRes();
    bool isImageComplete();
    void forEachPixelInParallel(
            const std::function<void(GLubyte& r, GLubyte& g, GLubyte& b, unsigned int x, unsigned int y)>& lambda
    );
private:
    void parallelSplit();
};
