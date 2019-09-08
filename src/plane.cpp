//
// plane.cpp
// Author: Samuel Vargas
// Date: 08/25/2019
//

#include "plane.h"
#include "ray.h"
#include <algorithm>
#include <glm/gtx/string_cast.hpp>
#include "mollertrumbore.h"

Plane::Plane(glm::vec3 origin, glm::vec3 normal, Material material) : Geometry(origin, material), normal(glm::normalize(normal)) {
}

Plane::~Plane() {
}

float Plane::getIntersectionScalarForRay(const Ray &ray) const {
    float denom = glm::dot(normal, ray.direction);
    glm::vec3 planeToRayDirection = origin - ray.origin;

    /*
    if (isEyeInFrontOfPlane(ray, origin)) {
        return -1.0f;
    }
     */


    // Plane normal and ray direction must be in opposition of each other
    // for an intersection to occur.
    if (denom >= 0) {
        return -1;
    }

    if (std::abs(denom) > 1e-2) {
        auto dot = glm::dot(planeToRayDirection, normal);
        float t = dot / denom;
        if (t >= 1e-4) {
            return t;
        }
    }

    return -1.0f;
}

glm::vec3 Plane::getSurfaceNormal(const glm::vec3& ignored) const {
    return normal;
}

std::ostream& operator<<(std::ostream& os, const Plane& sphere) {
    os << "Geometry Type: Plane, ";
    return os;
}
