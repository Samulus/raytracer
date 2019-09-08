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
    std::optional<RayCollision> calculatePixelColor(GLubyte& r, GLubyte& g, GLubyte& b, const RayCollision& rayCollision, const World& world) const override;
};

