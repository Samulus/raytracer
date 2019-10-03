//
// phonglighting.cpp
// Author: Samuel Vargas 
// Date: 09/25/2019
//

#include "phonglighting.h"

PhongLighting::PhongLighting() = default;

PhongLighting::~PhongLighting() = default;

std::optional<RayCollision>
PhongLighting::calculatePixelColor(
        GLubyte& r,
        GLubyte& g,
        GLubyte& b,
        const RayCollision& rayCollision,
        const World& world) const {
    return std::optional<RayCollision>();
}

void PhongLighting::addLight(std::unique_ptr<Light>& light) {
}

linalg::aliases::float3
PhongLighting::calculateLightContribution(const Light* light, const linalg::vec<float, 3>& intersectionPoint,
                                          const Geometry* hitObject) const {
    return linalg::aliases::float3();
}

void PhongLighting::calculateDiffuseColor(GLubyte& r, GLubyte& g, GLubyte& b, const RayCollision& rayCollision,
                                          const World& world) const {
}
