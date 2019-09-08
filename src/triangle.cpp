//
// triangle.cpp
// Author: Samuel Vargas 
// Date: 09/07/2019
//

#include "ray.h"
#include "triangle.h"
#include "mollertrumbore.h"

Triangle::Triangle(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2, const Material& material) :
    Geometry((v0 + v1 + v2) / 3.0f, material), v0(v0), v1(v1), v2(v2) {
}

Triangle::~Triangle() = default;

float Triangle::getIntersectionScalarForRay(const Ray& ray) const {
    return isRayIntersectingTriangle(ray, v0, v1, v2);
}

glm::vec3 Triangle::getSurfaceNormal(const glm::vec3& intersectionPoint) const {
    return getNormalForTriangle(v0, v1, v2);
}
