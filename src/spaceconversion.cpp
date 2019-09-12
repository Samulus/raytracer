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
                                       const glm::mat4& translationMatrix) {

    auto ray = pixelToPrimaryRay(x, y, width, height, fovDegrees);
    auto transOrigin = translationMatrix * glm::vec4(ray.origin, 1);
    return Ray(transOrigin, ray.direction);
}

Ray SpaceConversion::pixelToPrimaryRay(unsigned int x, unsigned int y, unsigned int width, unsigned int height,
                                       float fovDegrees) {
    auto ndc = rasterToNdc(x, y, width, height);
    auto screen = ndcToScreen(ndc);
    auto camera = screenToCamera(screen, float(width) / float(height), fovDegrees);
    return Ray(glm::vec3(), glm::normalize(glm::vec3(camera.x, camera.y, -1)), 0);
}

glm::vec2 SpaceConversion::rasterToNdc(unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
    const auto pixelNdcX = (float(x) + 0.5f) / float(width);
    const auto pixelNdcY = (float(y) + 0.5f) / float(height);
    return glm::vec2(pixelNdcX, pixelNdcY);
}

glm::vec2 SpaceConversion::ndcToScreen(const glm::vec2& ndcCoordinates) {
    auto pixelScreenX = 2.0f * ndcCoordinates.x - 1.0f;
    auto pixelScreenY = 1.0f - 2.0f * ndcCoordinates.y;
    return glm::vec2(pixelScreenX, pixelScreenY);
}

glm::vec2
SpaceConversion::screenToCamera(const glm::vec2& screenCoordinates, float imageAspectRatio, float fovDegrees) {
    auto rads = (fovDegrees * PI / 180.0f);
    auto fov = tanf(rads / 2.0f);
    float pixelCameraX = -1 * screenCoordinates.x * imageAspectRatio * fov;
    float pixelCameraY = -1 * screenCoordinates.y * fov;
    return glm::vec2(pixelCameraX, pixelCameraY);
}