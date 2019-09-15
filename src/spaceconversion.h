//
// spaceconversion.h
// Author: Samuel Vargas
// Date: 08/25/2019
//

#pragma once
#include "ray.h"
#include "pi.h"

namespace SpaceConversion {
    Ray pixelToPrimaryRay(unsigned int x, unsigned int y, unsigned int width, unsigned int height, float fovDegrees, const linalg::mat<float,4,4>& translationMatrix);
    Ray pixelToPrimaryRay(unsigned int x, unsigned int y, unsigned int width, unsigned int height, float fovDegrees);
    linalg::vec<float, 2> rasterToNdc(unsigned int x, unsigned int y, unsigned int width, unsigned int height);
    linalg::vec<float, 2> ndcToScreen(const linalg::vec<float, 2>& ndcCoordinates);
    linalg::vec<float, 2> screenToCamera(const linalg::vec<float, 2>& screenCoordinates, float imageAspectRatio, float fovDegrees);
};
