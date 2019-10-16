//
// coordinateconversion.cpp
// Author: Samuel Vargas 
// Date: 08/12/2019
//

#include "coordinateconversion.h"

// The ORIGIN is translated, but the direction is untouched
Ray CoordinateConversion::pixelToPrimaryRay(unsigned int x,
                                            unsigned int y,
                                            unsigned int width,
                                            unsigned int height,
                                            uint8_t fovDegrees,
                                            const linalg::aliases::float4x4& translationMatrix) {

    /*
    auto ray = imageCoordinateToPrimaryRay(x, y, width, height, fovDegrees);
    auto transOrigin = linalg::mul(translationMatrix, linalg::vec<float,4>(ray.origin, 1));
    return Ray(transOrigin, ray.direction);
     */
    throw std::runtime_error("Not implemented.");
}

Ray CoordinateConversion::imageCoordinateToPrimaryRay(
        size_t x,
        size_t y,
        size_t widthPx,
        size_t heightPx,
        uint8_t fovDegrees) {

    // Image Coordinates -> NDC Space ->

    auto ndc = rasterToNdc(x, y, widthPx, heightPx);
    auto screen = ndcToScreen(ndc);
    auto camera = screenToCamera(screen, float(widthPx) / float(heightPx), fovDegrees);
    auto origin = linalg::aliases::float3();
    auto camera3f = linalg::aliases::float3(camera, -1);
    auto direction = linalg::normalize(camera3f);
    return Ray(origin, direction);
}

linalg::vec<float,2> CoordinateConversion::rasterToNdc(
        unsigned int x,
        unsigned int y,
        unsigned int width,
        unsigned int height) {
    const auto pixelNdcX = (float(x) + 0.5f) / float(width);
    const auto pixelNdcY = (float(y) + 0.5f) / float(height);
    return linalg::vec<float,2>(pixelNdcX, pixelNdcY);
}

linalg::vec<float,2> CoordinateConversion::ndcToScreen(const linalg::vec<float,2>& ndcCoordinates) {
    auto pixelScreenX = 2.0f * ndcCoordinates.x - 1.0f;
    auto pixelScreenY = 1.0f - 2.0f * ndcCoordinates.y;
    return linalg::vec<float,2>(pixelScreenX, pixelScreenY);
}

linalg::vec<float,2>
CoordinateConversion::screenToCamera(
        const linalg::vec<float,2>& screenCoordinates,
        float imageAspectRatio,
        float fovDegrees) {
    auto rads = (fovDegrees * PI / 180.0f);
    auto fov = tanf(rads / 2.0f);
    float pixelCameraX = (2.0f * screenCoordinates.x - 1.0f) * imageAspectRatio * fov;
    float pixelCameraY = (-1.0f  - 2.0f * screenCoordinates.y) * fov;
    return linalg::vec<float,2>(pixelCameraX, pixelCameraY);
}