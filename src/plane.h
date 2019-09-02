//
// plane.h
// Author: Samuel Vargas
// Date: 08/25/2019
//

#pragma once

#include "geometry.h"
#include <iostream>
#include <glm/glm.hpp>

class Plane : public Geometry {
private:
    glm::vec3 normal;
public:
    Plane(glm::vec3 origin, glm::vec3 normal, Material material);
    ~Plane() override;
    [[nodiscard]] float getIntersectionScalarForRay(const Ray &ray) const override;
    [[nodiscard]] glm::vec3 getSurfaceNormal(const glm::vec3& intersectionPoint) const override;
    friend std::ostream& operator<<(std::ostream& os, const Plane& sphere);
};

