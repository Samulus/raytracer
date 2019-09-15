//
// spaceconversion.cpp
// Author: Samuel Vargas 
// Date: 08/12/2019
//

#include "spaceconversion.h"

// The ORIGIN is translated, but the direction is untouched
Ray SpaceConversion::pixelToPrimaryRay(unsigned int x,
                                       unsigned int y,
                                       unsigned int width,
                                       unsigned int height,
                                       float fovDegrees,
                                       const linalg::mat<float, 4, 4>& translationMatrix) {

    /*
    auto ray = pixelToPrimaryRay(x, y, width, height, fovDegrees);
    auto transOrigin = linalg::mul(translationMatrix, linalg::vec<float,4>(ray.origin, 1));
    return Ray(transOrigin, ray.direction);
     */
    throw std::runtime_error("Not implemented.");
}

Ray SpaceConversion::pixelToPrimaryRay(unsigned int x, unsigned int y, unsigned int width, unsigned int height,
                                       float fovDegrees) {
    auto ndc = rasterToNdc(x, y, width, height);
    auto screen = ndcToScreen(ndc);
    auto camera = screenToCamera(screen, float(width) / float(height), fovDegrees);
    return Ray(linalg::vec<float,3>(), linalg::normalize(linalg::vec<float,3>(camera.x, camera.y, -1)), 0);
}

linalg::vec<float,2> SpaceConversion::rasterToNdc(unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
    const auto pixelNdcX = (float(x) + 0.5f) / float(width);
    const auto pixelNdcY = (float(y) + 0.5f) / float(height);
    return linalg::vec<float,2>(pixelNdcX, pixelNdcY);
}

linalg::vec<float,2> SpaceConversion::ndcToScreen(const linalg::vec<float,2>& ndcCoordinates) {
    auto pixelScreenX = 2.0f * ndcCoordinates.x - 1.0f;
    auto pixelScreenY = 1.0f - 2.0f * ndcCoordinates.y;
    return linalg::vec<float,2>(pixelScreenX, pixelScreenY);
}

linalg::vec<float,2>
SpaceConversion::screenToCamera(const linalg::vec<float,2>& screenCoordinates, float imageAspectRatio, float fovDegrees) {
    auto rads = (fovDegrees * PI / 180.0f);
    auto fov = tanf(rads / 2.0f);
    float pixelCameraX = -1 * screenCoordinates.x * imageAspectRatio * fov;
    float pixelCameraY = -1 * screenCoordinates.y * fov;
    return linalg::vec<float,2>(pixelCameraX, pixelCameraY);
}