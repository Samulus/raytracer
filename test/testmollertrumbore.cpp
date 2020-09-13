//
// testmollertrumbore.cpp
// Author: Samuel Vargas
// Date: 09/02/2019
//

#include <doctest/doctest.h>
#include <vector>
#include "mollertrumbore.h"

TEST_CASE("getNormalForTriangle()") {
    const auto v0 = linalg::vec<float,3>(-1, -1, 0);
    const auto v1 = linalg::vec<float,3>(1, -1, 0);
    const auto v2 = linalg::vec<float,3>(0, 1, 0);

    const std::vector<std::vector<linalg::vec<float,3>>> ccwPermutations = {
        {v0, v1, v2}, {v1, v2, v0}, {v2, v0, v1}
    };

    const std::vector<std::vector<linalg::vec<float,3>>> cwPermutations = {
        {v2, v1, v0}, {v1, v0, v2}, {v0, v2, v1}
    };

    // ccwPermutations produce positive normals
    for (const auto& perm : ccwPermutations) {
        const auto result = getNormalForTriangle(perm[0], perm[1], perm[2]);
        REQUIRE(result.x == doctest::Approx(0));
        REQUIRE(result.y == doctest::Approx(0));
        REQUIRE(result.z == doctest::Approx(4));
    }

    // cwPermutations produce negative normals
    for (const auto& perm : cwPermutations) {
        const auto result = getNormalForTriangle(perm[0], perm[1], perm[2]);
        REQUIRE(result.x == doctest::Approx(0));
        REQUIRE(result.y == doctest::Approx(0));
        REQUIRE(result.z == doctest::Approx(-4));
    }
}

TEST_CASE("pointIsInsideTheTriangle") {
    const auto v0 = linalg::vec<float,3>(0, 1, 0);
    const auto v1 = linalg::vec<float,3>(1, 0 ,0);
    const auto v2 = linalg::vec<float,3>(-1, 0, 0);
    const auto n = linalg::vec<float,3>(0, 0, -1);

    // Fail if directly on edge of triangle.
    REQUIRE(!pointIsInsideTheTriangle(linalg::vec<float,3>(0, 0, 0), n, v0, v1, v2));
    REQUIRE(!pointIsInsideTheTriangle(linalg::vec<float,3>(0, 1, 0), n, v0, v1, v2));
    REQUIRE(!pointIsInsideTheTriangle(linalg::vec<float,3>(-1, 0, 0), n, v0, v1, v2));

    // Pass if inside triangle
    REQUIRE(pointIsInsideTheTriangle(linalg::vec<float,3>(0, 0.1, 0), n, v0, v1, v2));
    REQUIRE(pointIsInsideTheTriangle(linalg::vec<float,3>(-0.9, 0.1, 0), n, v0, v1, v2));

    // >= 0.9 will fail due to floating point rounding errors, we can ignore this visually
    REQUIRE(pointIsInsideTheTriangle(linalg::vec<float,3>(0.89, 0.1, 0), n, v0, v1, v2));
}

TEST_CASE("isRayIntersectingTriangle()") {
    const auto v0 = linalg::vec<float,3>(0, 1, -1);
    const auto v1 = linalg::vec<float,3>(1, 0 ,-1);
    const auto v2 = linalg::vec<float,3>(-1, 0, -1);

    // Collision Occurs
    SUBCASE("Eye behind triangle, eye is looking at triangle, triangle is looking at eye, collision occurs") {
        const auto eyeRay = Ray(linalg::vec<float,3>(0, 0.5, 0), linalg::vec<float,3>(0, 0, -1));
        // positive normal
        REQUIRE(isRayIntersectingTriangle(eyeRay, v0, v2, v1) > 0);
    }

    // No Collision Occurs
    SUBCASE("Eye behind triangle, eye is looking at triangle, but triangle is facing away from viewer, no collision") {
        const auto eyeRay = Ray(linalg::vec<float,3>(0, 0.5, 0), linalg::vec<float,3>(0, 0, -1));
        REQUIRE(isRayIntersectingTriangle(eyeRay, v0, v1, v2) < 0);
    }

    SUBCASE("Eye in front of triangle, eye is looking in same direction as triangle, no collision") {
        const auto eyeRay = Ray(linalg::vec<float,3>(0, 0.5, -2), linalg::vec<float,3>(0, 0, 1));
        REQUIRE(isRayIntersectingTriangle(eyeRay, v0, v2, v1) < 0);
    }

    SUBCASE("Eye in front of triangle, eye and triangle normals oppose each other, no collision") {
        const auto eyeRay = Ray(linalg::vec<float,3>(0, 0.5, -2), linalg::vec<float,3>(0, 0, -1));
        REQUIRE(isRayIntersectingTriangle(eyeRay, v0, v2, v1) < 0);
    }
}
