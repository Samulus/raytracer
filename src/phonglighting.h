//
// phonglighting.h
// Author: Samuel Vargas 
// Date: 09/25/2019
//

#pragma once
#include "lighttransport.h"

class PhongLighting : LightTransport {
private:
    std::vector<std::unique_ptr<Light>> lights;
public:
    PhongLighting();
    ~PhongLighting() override;
    std::optional<RayCollision> calculatePixelColor(GLubyte& r, GLubyte& g, GLubyte& b, const RayCollision& rayCollision, const World& world) const override;
    void addLight(std::unique_ptr<Light>& light);
    linalg::aliases::float3 calculateLightContribution(const Light* light, const linalg::vec<float,3>& intersectionPoint, const Geometry* hitObject) const;
private:
    void calculateDiffuseColor(GLubyte& r, GLubyte& g, GLubyte& b, const RayCollision& rayCollision, const World& world) const;
};

