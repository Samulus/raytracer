//
// triangle.cpp
// Author: Samuel Vargas 
// Date: 09/07/2019
//

#include "ray.h"
#include "triangle.h"
#include "mollertrumbore.h"

Triangle::Triangle(const linalg::vec<float,3>& v0, const linalg::vec<float,3>& v1, const linalg::vec<float,3>& v2, const linalg::vec<float,3>& normal, const Material& material) :
    Geometry((v0 + v1 + v2) / 3.0f, material), v0(v0), v1(v1), v2(v2), normal(normal) {
}

Triangle::~Triangle() = default;

float Triangle::getIntersectionScalarForRay(const Ray& ray) const {
    return isRayIntersectingTriangle(ray, v0, v1, v2, normal);
}

linalg::vec<float,3> Triangle::getSurfaceNormal(const linalg::vec<float,3>& intersectionPoint) const {
    return normal;
}
