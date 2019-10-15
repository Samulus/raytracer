//
// rgbimagethreaded.cpp
// Author: Samuel Vargas
// Date: 10/12/2019
//

#include "rgbimagethreaded.h"
#include <stdexcept>
#include <spdlog/spdlog.h>
#include <iostream>

RGBImageThreaded::RGBImageThreaded(unsigned int threadCount, unsigned int xRes, unsigned int yRes) :
        xRes(xRes), yRes(yRes),
        threads(std::vector<std::thread>()),
        byteData(std::vector<GLubyte>(xRes * yRes * 3, 0)),
        activeThreadCount(0) {

    if (threadCount == 0) {
        throw std::logic_error("threadCount was 0");
    }

    for (unsigned int i = 0; i < threadCount; ++i) {
        threads.emplace_back(std::thread());
    }
}

RGBImageThreaded::~RGBImageThreaded() = default;

const std::vector<GLubyte> &RGBImageThreaded::getPixelData() const {
    return this->byteData;
}

unsigned int RGBImageThreaded::getXRes() {
    return xRes;
}

unsigned int RGBImageThreaded::getYRes() {
    return yRes;
}

bool RGBImageThreaded::isImageBeingGenerated() {
    if (this->imageGenerationMutex.try_lock()) {
        this->imageGenerationMutex.unlock();
        return false;
    }

    return true;
}

void RGBImageThreaded::forEachPixelInParallel(
        const std::function<void(GLubyte &r, GLubyte &g, GLubyte &b, unsigned int x, unsigned int y)> &lambda) {

    if (!this->imageGenerationMutex.try_lock()) {
        throw std::runtime_error("Thread already running");
    }

    spdlog::trace("RGBImageThreaded -> Locking Thread(s)");

    const auto callLambdaWithBytes = [&](size_t startIndex, size_t endIndex) {
        for (size_t i = startIndex; i < endIndex; i += 3) {
            auto x = static_cast<size_t>((i / 3) % xRes);
            auto y = static_cast<size_t>((i / 3) / xRes);
            lambda.operator()(byteData[i], byteData[i + 1], byteData[i + 2], x, y);
        }
        activeThreadCount--;
        if (activeThreadCount == 0) {
            spdlog::trace("RGBImageThreaded:: All Thread(s) Complete");
            this->imageGenerationMutex.unlock();
        }
    };


    size_t threadPixelWorkload = (byteData.size() / threads.size()) - 1;
    size_t lastIndex = 0;
    spdlog::trace("RGBImageThreaded -> Spawning Threads");

    for (auto &t : threads) {
        size_t startIndex = lastIndex;
        size_t endIndex = lastIndex + threadPixelWorkload;
        lastIndex += threadPixelWorkload + 1;
        activeThreadCount++;
        t = std::thread{callLambdaWithBytes, startIndex, endIndex};
        t.detach();
    }

    spdlog::trace("RGBImageThreaded -> Threads Running in Background");
}

