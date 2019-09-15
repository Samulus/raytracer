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
    linalg::vec<float,3> origin;
public:
    Geometry(const linalg::vec<float,3>& origin, const Material& material) : origin(origin), material(material) {};
    virtual ~Geometry() = 0;
    [[nodiscard]] virtual float getIntersectionScalarForRay(const Ray& ray) const = 0;
    [[nodiscard]] Material getMaterial() const { return material; }
    [[nodiscard]] virtual linalg::vec<float,3> getSurfaceNormal(const linalg::vec<float,3>& intersectionPoint) const = 0;
};

