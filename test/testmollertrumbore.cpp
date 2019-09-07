//
// testmollertrumbore.cpp
// Author: Samuel Vargas 
// Date: 09/02/2019
//

#include <doctest/doctest.h>
#include <vector>
#include <array>
#include "mollertrumbore.h"

TEST_CASE("getNormalForTriangle()") {
    const auto v0 = glm::vec3(-1, -1, 0);
    const auto v1 = glm::vec3(1, -1, 0);
    const auto v2 = glm::vec3(0, 1, 0);

    const std::vector<std::vector<glm::vec3>> ccwPermutations = {
        {v0, v1, v2}, {v1, v2, v0}, {v2, v0, v1}
    };

    const std::vector<std::vector<glm::vec3>> cwPermutations = {
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
    const auto v0 = glm::vec3(0, 1, 0);
    const auto v1 = glm::vec3(1, 0 ,0);
    const auto v2 = glm::vec3(-1, 0, 0);
    const auto n = glm::vec3(0, 0, -1);

    // Fail if directly on edge of triangle.
    REQUIRE(!pointIsInsideTheTriangle(glm::vec3(0, 0, 0), n, v0, v1, v2));
    REQUIRE(!pointIsInsideTheTriangle(glm::vec3(0, 1, 0), n, v0, v1, v2));
    REQUIRE(!pointIsInsideTheTriangle(glm::vec3(-1, 0, 0), n, v0, v1, v2));

    // Pass if inside triangle
    REQUIRE(pointIsInsideTheTriangle(glm::vec3(0, 0.1, 0), n, v0, v1, v2));
    REQUIRE(pointIsInsideTheTriangle(glm::vec3(-0.9, 0.1, 0), n, v0, v1, v2));

    // >= 0.9 will fail due to floating point rounding errors, we can ignore this visually
    REQUIRE(pointIsInsideTheTriangle(glm::vec3(0.89, 0.1, 0), n, v0, v1, v2));
}

TEST_CASE("isRayIntersectingTriangle()") {

    const auto v0 = glm::vec3(0, 1, -1);
    const auto v1 = glm::vec3(1, 0 ,-1);
    const auto v2 = glm::vec3(-1, 0, -1);

    SUBCASE("Viewer looking at triangle, but triangle is facing away from viewer.") {
        const auto eyeRay = Ray(glm::vec3(0, 0.5, 0), glm::vec3(0, 0, -1));
        REQUIRE(isRayIntersectingTriangle(eyeRay, v0, v1, v2) < 0);
    }

    SUBCASE("Viewer looking at triangle and triangle is facing viewer.") {
        const auto eyeRay = Ray(glm::vec3(0, 0.5, 0), glm::vec3(0, 0, -1));
        REQUIRE(isRayIntersectingTriangle(eyeRay, v0, v2, v1) > 0);
    }



}

/*
TEST_CASE("Möller-Trumbore implementation respects face occlusion") {
    // CCW order
    const auto v0 = glm::vec3(0, 1, 0); //  v0
    const auto v1 = glm::vec3(0, 0, 0); //  . .
    const auto v2 = glm::vec3(1, 0, 0); //  v1.v2
    const auto normal = glm::vec3(0, 0, 1); // Triangle is front-facing.

    const auto frontIntersection = Ray(glm::vec3(0.5, 0.5, 1), glm::vec3(0, 0, -1));
    const auto frontScalar = mollertrumboreIntersection(frontIntersection, v0, v1, v2, normal);
    REQUIRE(frontScalar > 0);

    const auto rearIntersection = Ray(glm::vec3(0.5, 0.5, -1), glm::vec3(0, 0, 1));
    const auto rearScalar = mollertrumboreIntersection(rearIntersection, v0, v1, v2, normal);
    REQUIRE(rearScalar < 0);
}
 */
