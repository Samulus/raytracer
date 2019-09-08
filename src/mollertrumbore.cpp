//
// mollertrumbore.cpp
// Author: Samuel Vargas 
// Date: 09/03/2019
//
// NOTES:
//  - We can invert the camera and the normal if it doesn't match the coordinate syste (LHS)
//    we're using.

#include "mollertrumbore.h"

const auto TRIANGLE_PARALLEL_EPSILON = 1e-4;
constexpr glm::vec3 FORWARD_VECTOR = glm::vec3(0, 0, -1);

glm::vec3 getNormalForTriangle(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2) {
    return glm::cross(v1 - v0, v2 - v0);
}

bool isEyeInFrontOfPlane(const Ray& ray, const glm::vec3& arbitraryPlanePoint ) {
    const auto eyeToVertex = arbitraryPlanePoint - ray.origin;
    const auto eyeDotForward = glm::dot(eyeToVertex, FORWARD_VECTOR);
    return eyeDotForward <= 0;
}

bool pointIsInsideTheTriangle(const glm::vec3& p, const glm::vec3& n, const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2) {
    const auto e0 = v1 - v0;
    const auto c0 = p - v0;
    const auto cross0 = glm::cross(e0, c0);
    const auto t0 = glm::dot(n, cross0);

    if (t0 <= 0) {
        return false;
    }

    const auto e1 = v2 - v1;
    const auto c1 = p - v1;
    const auto cross1 = glm::cross(e1, c1);
    const auto t1 = glm::dot(n, cross1);

    if (t1 <= 0) {
        return false;
    }

    const auto e2 = v0 - v2;
    const auto c2 = p - v2;
    const auto cross2 = glm::cross(e2, c2);
    const auto t2 = glm::dot(n, cross2);
    return t2 > 0;
}


float isRayIntersectingTriangle(
        const Ray& ray,
        const glm::vec3& v0,
        const glm::vec3& v1,
        const glm::vec3& v2,
        bool isSingleSided) {

    if (isEyeInFrontOfPlane(ray, v0)) {
        return -1;
    }

    const auto triangleNormal = getNormalForTriangle(v0, v1, v2);
    const auto doubleSidedDot = glm::dot(ray.direction, glm::normalize(triangleNormal));

    if (doubleSidedDot > 0 && isSingleSided) {
        return -1.0f;
    }

    // Ray is parallel to triangle → No Collision
    const auto rayPlaneDotProduct = glm::dot(triangleNormal, ray.direction);
    if (std::abs(rayPlaneDotProduct) < TRIANGLE_PARALLEL_EPSILON) {
        return -1.0f;
    }

    const auto d = glm::dot(triangleNormal, v0);
    const auto numerator = glm::dot(triangleNormal, ray.origin) + d;
    const auto intersectionScalar = -numerator / rayPlaneDotProduct;

    // Triangle is BEHIND the ray.
    if (intersectionScalar < 0) {
        return -1.0f;
    }

    const auto intersectionPoint = ray.pointWithScalar(intersectionScalar);
    if (!pointIsInsideTheTriangle(intersectionPoint, triangleNormal, v0, v1, v2)) {
        return -1.0f;
    }

    return intersectionScalar;
}
