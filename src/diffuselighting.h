//
// diffuselighting.h
// Author: Samuel Vargas
// Date: 08/23/2019
//

#pragma once

#include "linalg.h"
#include "lighttransport.h"
#include "light.h"
#include <memory>

class DiffuseLighting : public LightTransport {
private:
    std::vector<std::unique_ptr<Light>> lights;
public:
    DiffuseLighting() = default;
    ~DiffuseLighting() override;
    std::optional<RayCollision> calculatePixelColor(GLubyte& r, GLubyte& g, GLubyte& b, const RayCollision& rayCollision, const World& world) const override;
    void addLight(std::unique_ptr<Light>& light);
    [[nodiscard]] std::optional<RayCollision> rayIntersectsAnyGeometry(
            const Ray& occlusionRay,
            const World& world,
            float maxScalarDistance) const;
    linalg::vec<float,3> calculateLightContribution(const Light* light, const linalg::vec<float,3>& intersectionPoint, const Geometry* hitObject) const;
private:
    void calculateDiffuseColor(GLubyte& r, GLubyte& g, GLubyte& b, const RayCollision& rayCollision, const World& world) const;
};
