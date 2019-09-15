//
// sphere.h
// Author: Samuel Vargas
// Date: 08/25/2019
//

#pragma once
#include <iostream>
#include "geometry.h"

class Sphere : public Geometry {
private:
    const float radius;
public:
    Sphere(linalg::vec<float,3> origin, float radius, Material material);
    ~Sphere() override = default;
    [[ nodiscard ]] float getIntersectionScalarForRay(const Ray &ray) const override;
    [[ nodiscard ]] linalg::vec<float,3> getSurfaceNormal(const linalg::vec<float,3>& ignored) const override ;
    friend std::ostream& operator<<(std::ostream& os, const Sphere& obj);
};

