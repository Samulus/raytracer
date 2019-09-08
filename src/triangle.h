//
// triangle.h
// Author: Samuel Vargas 
// Date: 09/07/2019
//

#pragma once
#include "geometry.h"

class Triangle : public Geometry {
    glm::vec3 v0;
    glm::vec3 v1;
    glm::vec3 v2;
public:
    Triangle(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2, const Material& material);
    ~Triangle() override;
    [[nodiscard]] float getIntersectionScalarForRay(const Ray& ray) const override;
    [[nodiscard]] glm::vec3 getSurfaceNormal(const glm::vec3& intersectionPoint) const override;
};
