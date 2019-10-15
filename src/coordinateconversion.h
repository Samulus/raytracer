//
// coordinateconversion.h
// Author: Samuel Vargas
// Date: 08/25/2019
//

#pragma once
#include "ray.h"
#include "pi.h"

namespace CoordinateConversion {
    Ray pixelToPrimaryRay(unsigned int x, unsigned int y, unsigned int width, unsigned int height, uint8_t fovDegrees, const linalg::mat<float,4,4>& translationMatrix);
    Ray imageCoordinateToPrimaryRay(size_t x, size_t y, size_t widthPx, size_t heightPx, uint8_t fovDegrees);
    linalg::vec<float, 2> rasterToNdc(unsigned int x, unsigned int y, unsigned int width, unsigned int height);
    linalg::vec<float, 2> ndcToScreen(const linalg::vec<float, 2>& ndcCoordinates);
    linalg::vec<float, 2> screenToCamera(const linalg::vec<float, 2>& screenCoordinates, float imageAspectRatio, float fovDegrees);
};
