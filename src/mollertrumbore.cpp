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
constexpr linalg::vec<float,3> FORWARD_VECTOR = linalg::vec<float,3>(0, 0, -1);

linalg::vec<float,3> getNormalForTriangle(const linalg::vec<float,3>& v0, const linalg::vec<float,3>& v1, const linalg::vec<float,3>& v2) {
    return linalg::cross(v1 - v0, v2 - v0);
}

bool isEyeInFrontOfPlane(const Ray& ray, const linalg::vec<float,3>& arbitraryPlanePoint ) {
    const auto eyeToVertex = arbitraryPlanePoint - ray.origin;
    const auto eyeDotForward = linalg::dot(eyeToVertex, FORWARD_VECTOR);
    return eyeDotForward <= 0;
}

bool pointIsInsideTheTriangle(const linalg::vec<float,3>& p, const linalg::vec<float,3>& n, const linalg::vec<float,3>& v0, const linalg::vec<float,3>& v1, const linalg::vec<float,3>& v2) {
    const auto e0 = v1 - v0;
    const auto c0 = p - v0;
    const auto cross0 = linalg::cross(e0, c0);
    const auto t0 = linalg::dot(n, cross0);

    if (t0 <= 0) {
        return false;
    }

    const auto e1 = v2 - v1;
    const auto c1 = p - v1;
    const auto cross1 = linalg::cross(e1, c1);
    const auto t1 = linalg::dot(n, cross1);

    if (t1 <= 0) {
        return false;
    }

    const auto e2 = v0 - v2;
    const auto c2 = p - v2;
    const auto cross2 = linalg::cross(e2, c2);
    const auto t2 = linalg::dot(n, cross2);
    return t2 > 0;
}


float isRayIntersectingTriangle(
        const Ray& ray,
        const linalg::vec<float,3>& v0,
        const linalg::vec<float,3>& v1,
        const linalg::vec<float,3>& v2,
        const std::optional<linalg::vec<float,3>> normal,
        bool isSingleSided) {

    if (isEyeInFrontOfPlane(ray, v0)) {
        return -1;
    }

    const auto triangleNormal = normal == std::nullopt ? getNormalForTriangle(v0, v1, v2) : normal.value();
    const auto doubleSidedDot = linalg::dot(ray.direction, linalg::normalize(triangleNormal));

    if (doubleSidedDot > 0 && isSingleSided) {
        return -1.0f;
    }

    // Ray is parallel to triangle → No Collision
    const auto rayPlaneDotProduct = linalg::dot(triangleNormal, ray.direction);
    if (std::abs(rayPlaneDotProduct) < TRIANGLE_PARALLEL_EPSILON) {
        return -1.0f;
    }

    const auto d = linalg::dot(triangleNormal, v0);
    // TODO: Why does scratch a pixel use the ray origin instead of ray direction here?
    //       I get incorrect results when using their algorithm.
    const auto numerator = linalg::dot(triangleNormal, ray.direction) + d;
    const auto intersectionScalar = numerator / rayPlaneDotProduct;

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

float mollertrumboreIntersection(
        const Ray& ray,
        const linalg::vec<float,3>& v0,
        const linalg::vec<float,3>& v1,
        const linalg::vec<float,3>& v2,
        const linalg::vec<float,3>& ignored) {

    if (isEyeInFrontOfPlane(ray, v0)) {
        return -1;
    }

    const auto triangleNormal = getNormalForTriangle(v0, v1, v2);
    const auto doubleSidedDot = linalg::dot(ray.direction, linalg::normalize(triangleNormal));

    // TODO: We assume everything is single sided right now.
    if (doubleSidedDot > 0) {
        return -1.0f;
    }

    // Ray is parallel to triangle → No Collision
    const auto rayPlaneDotProduct = linalg::dot(triangleNormal, ray.direction);
    if (std::abs(rayPlaneDotProduct) < TRIANGLE_PARALLEL_EPSILON) {
        return -1.0f;
    }

    const auto d = linalg::dot(triangleNormal, v0);
    // TODO: Why does scratch a pixel use the ray origin instead of ray direction here?
    //       I get incorrect results when using their algorithm.
    const auto numerator = linalg::dot(triangleNormal, ray.direction) + d;
    const auto intersectionScalar = numerator / rayPlaneDotProduct;

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

