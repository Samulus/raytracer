//
// facingratiolighttransport.cpp
// Author: Samuel Vargas
// Date: 08/25/2019
//

#include "facingratiolighttransport.h"
#include <algorithm>

/**
 * Primitive shading technique using the dot product of the surface normal (geometry->getSurfaceNormal())
 * and viewing angle (primaryRay).
 * The dot product of the surface normal with the reflected viewing angle tells us how "bright" this
 * intersection should be.
 *
 * @param r Red amount
 * @param g Green amount
 * @param b Blue amount
 * @param primaryRay Primary ray casted into object
 * @param intersectionPoint The intersection point (e.g primaryRay * t = intersectionPoint)
 * @param geometry The intersected object
 */

std::optional<RayCollision> FacingRatioLightTransport::calculatePixelColor(GLubyte& r, GLubyte& g, GLubyte& b, const RayCollision& rayCollision, const World& world) const {
    const auto& color = rayCollision.hitObject.value().get()->getMaterial().color;
    const auto& surfaceNormal = rayCollision.hitObject.value().get()->getSurfaceNormal(rayCollision.intersectionPoint);
    float ratio = std::max(0.0f, glm::dot(surfaceNormal, -rayCollision.ray.direction));
    r = ratio * color.r * 255.0f;
    g = ratio * color.g * 255.0f;
    b = ratio * color.b * 255.0f;
    return std::nullopt;
}

FacingRatioLightTransport::~FacingRatioLightTransport() = default;
