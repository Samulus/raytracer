//
// rgbimagethreaded.cpp
// Author: Samuel Vargas
// Date: 10/12/2019
//

#include "rgbimagethreaded.h"
#include <stdexcept>

RGBImageThreaded::RGBImageThreaded(unsigned int threadCount, unsigned int xRes, unsigned int yRes) :
    xRes(xRes), yRes(yRes), threads(std::vector<std::thread>()), byteData(std::vector<GLubyte>(xRes * yRes * 3, 0)) {

    if (threadCount == 0) {
        throw std::logic_error("threadCount was 0");
    }

    for (unsigned int i=0; i < threadCount; ++i) {
        threads.emplace_back(std::thread());
    }
}

RGBImageThreaded::~RGBImageThreaded() = default;

const std::vector<GLubyte>& RGBImageThreaded::getPixelData() {
    return this->byteData;
}

unsigned int RGBImageThreaded::getXRes() {
    return xRes;
}

unsigned int RGBImageThreaded::getYRes() {
    return yRes;
}

bool RGBImageThreaded::isImageComplete() {
    std::unique_lock<std::mutex> guard(lock);
    return guard.try_lock();
}

void RGBImageThreaded::forEachPixelInParallel(
        const std::function<void(GLubyte &r, GLubyte &g, GLubyte &b, unsigned int x, unsigned int y)> &lambda) {

    const auto callLambdaWithBytes = [&](unsigned int startIndex, unsigned int endIndex) {
        for (unsigned int i=startIndex; i < endIndex; i += 3) {
            auto x = (i / 3) % xRes;
            auto y = (i / 3) / xRes;
            lambda.operator()(byteData[i], byteData[i + 1], byteData[i + 2], x, y);
        }
    };

    std::lock_guard<std::mutex> guard(lock);

    unsigned int threadPixelWorkload = (byteData.size() / threads.size()) - 1;
    unsigned int lastIndex = 0;
    for (auto& t : threads) {
        unsigned int startIndex = lastIndex;
        unsigned int endIndex = lastIndex + threadPixelWorkload;
        lastIndex += threadPixelWorkload + 1;
        t = std::thread {callLambdaWithBytes, startIndex, endIndex };
    }
}

