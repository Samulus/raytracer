//
// geometry.h
// Author: Samuel Vargas
// Date: 08/25/2019
//

#pragma once

#include "ray.h"
#include "material.h"

class Geometry {
protected:
    Material material;
    glm::vec3 origin;
public:
    Geometry(const glm::vec3& origin, const Material& material) : origin(origin), material(material) {};
    virtual ~Geometry() = 0;
    [[nodiscard]] virtual float getIntersectionScalarForRay(const Ray& ray) const = 0;
    [[nodiscard]] Material getMaterial() const { return material; }
    [[nodiscard]] virtual glm::vec3 getSurfaceNormal(const glm::vec3& intersectionPoint) const = 0;
};

