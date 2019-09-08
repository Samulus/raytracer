//
// sphere.cpp
// Author: Samuel Vargas
// Date: 08/13/2019
//

#include "sphere.h"
#include "ray.h"
#include <glm/gtx/string_cast.hpp>

Sphere::Sphere(glm::vec3 origin, float radius, Material material) :
Geometry(origin, material), radius(radius) {
}

float Sphere::getIntersectionScalarForRay(const Ray& ray) const {
    auto oc = ray.origin - Geometry::origin;
    float a = glm::dot(ray.direction, ray.direction);
    float b = 2.0f * glm::dot(oc, ray.direction);
    float c = glm::dot(oc,oc) - radius * radius;
    float discriminant = b*b - 4*a*c;
    if (discriminant < 0.0){
        return -1.0;
    }

    float numerator = -b - sqrtf(discriminant);
    if (numerator > 0.0) {
        return numerator / (2.0f * a);
    }

    numerator = -b + sqrtf(discriminant);
    if (numerator > 0.0) {
        return numerator / (2.0f * a);
    }

    return -1.0f;
}

glm::vec3 Sphere::getSurfaceNormal(const glm::vec3& intersectionPoint) const {
    return glm::normalize(intersectionPoint - Geometry::origin);
}

std::ostream& operator<<(std::ostream& os, const Sphere& sphere) {
    os << "Geometry Type: Sphere, ";
    return os;
}