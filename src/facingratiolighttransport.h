//
// facingratiolighttransport.h
// Author: Samuel Vargas
// Date: 08/25/2019
//

#pragma once

#include "lighttransport.h"

class FacingRatioLightTransport : public LightTransport {
public:
    FacingRatioLightTransport() = default;
    ~FacingRatioLightTransport() override;
    std::optional<Ray> calculatePixelColor(GLubyte& r, GLubyte& g, GLubyte& b,
                             Ray& primaryRay,
                             const glm::vec3& intersectionPoint,
                             const Geometry& geometry,
                             const World& world);
};

