//
// triangle.h
// Author: Samuel Vargas 
// Date: 09/07/2019
//

#pragma once
#include "geometry.h"

class Triangle : public Geometry {
    linalg::vec<float,3> v0;
    linalg::vec<float,3> v1;
    linalg::vec<float,3> v2;
    linalg::vec<float,3> normal;
public:
    Triangle(const linalg::vec<float,3>& v0, const linalg::vec<float,3>& v1, const linalg::vec<float,3>& v2, const linalg::vec<float,3>& normal, const Material& material);
    ~Triangle() override;
    [[nodiscard]] float getIntersectionScalarForRay(const Ray& ray) const override;
    [[nodiscard]] linalg::vec<float,3> getSurfaceNormal(const linalg::vec<float,3>& intersectionPoint) const override;
};
