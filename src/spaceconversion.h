//
// spaceconversion.h
// Author: Samuel Vargas
// Date: 08/25/2019
//

#pragma once
#include <glm/glm.hpp>
#include "ray.h"
#include "pi.h"

namespace SpaceConversion {
    Ray pixelToPrimaryRay(unsigned int x, unsigned int y, unsigned int width, unsigned int height, float fovDegrees, const glm::mat4& translationMatrix);
    Ray pixelToPrimaryRay(unsigned int x, unsigned int y, unsigned int width, unsigned int height, float fovDegrees);
    glm::vec2 rasterToNdc(unsigned int x, unsigned int y, unsigned int width, unsigned int height);
    glm::vec2 ndcToScreen(const glm::vec2& ndcCoordinates);
    glm::vec2 screenToCamera(const glm::vec2& screenCoordinates, float imageAspectRatio, float fovDegrees);
};
