//
// plane.h
// Author: Samuel Vargas
// Date: 08/25/2019
//

#pragma once

#include "geometry.h"
#include <iostream>

class Plane : public Geometry {
private:
    linalg::vec<float,3> normal;
public:
    Plane(linalg::vec<float,3> origin, linalg::vec<float,3> normal, Material material);
    ~Plane() override;
    [[nodiscard]] float getIntersectionScalarForRay(const Ray &ray) const override;
    [[nodiscard]] linalg::vec<float,3> getSurfaceNormal(const linalg::vec<float,3>& intersectionPoint) const override;
    friend std::ostream& operator<<(std::ostream& os, const Plane& sphere);
};

