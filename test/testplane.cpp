//
// testplane.cpp
// Author: Samuel Vargas
// Date: 08/25/2019
//

#include <doctest/doctest.h>
#include "color.h"
#include "plane.h"
#include "albedo.h"

/*
TEST_CASE("Plane @ (0,0,-1) with normal (0,0,1) visible from (0,0,0) looking at (0,0,-1)") {
    const auto eyeOrigin = glm::vec3(0,0,0);
    const auto eyeDirection = glm::vec3(0, 0, -1);
    const auto eyeRay = Ray(eyeOrigin, eyeDirection, 0);

    const auto planeOrigin = glm::vec3(0, 0, -1);
    const auto planeNormal = glm::vec3(0, 0, 1);
    const auto OPAQUE_WHITE = Material(WHITE, AVERAGE_ALBEDO, MaterialType::Diffuse, 0);
    const auto wall = Plane(planeOrigin, planeNormal, OPAQUE_WHITE);
    const auto scalar = wall.getIntersectionScalarForRay(eyeRay);
    REQUIRE(scalar > 0);
}

TEST_CASE("Plane @ (0,0,-1.01) with normal (0,0, -1), is not visible from (0,0,0) looking at (0, 0, -1") {
    const auto eyeOrigin = glm::vec3(0,0,0);
    const auto eyeDirection = glm::vec3(0, 0, -1);
    const auto eyeRay = Ray(eyeOrigin, eyeDirection, 0);

    const auto planeOrigin = glm::vec3(0, 0, -1.01);
    const auto planeNormal = glm::vec3(0, 0, -1);

    const auto wall = Plane(WHITE, AVERAGE_ALBEDO, planeOrigin, planeNormal, 0.1f);
    const auto scalar = wall.getIntersectionScalarForRay(eyeRay);
    REQUIRE(scalar < 0);
}

TEST_CASE("Plane @ (0,0,-1.01) with normal (0,0, +1), is not visible from (0,0,0) looking at (0,0, -1") {
    const auto eyeOrigin = glm::vec3(0,0,0);
    const auto eyeDirection = glm::vec3(0, 0, -1);
    const auto eyeRay = Ray(eyeOrigin, eyeDirection, 0);

    const auto planeOrigin = glm::vec3(0, 0, -1.01);
    const auto planeNormal = glm::vec3(0, 0, 1);

    const auto wall = Plane(WHITE, AVERAGE_ALBEDO, planeOrigin, planeNormal, 0.1f);
    const auto scalar = wall.getIntersectionScalarForRay(eyeRay);
    REQUIRE(scalar < 0);
}


TEST_CASE("Plane facing is intersecting") {
    const auto planeOrigin = glm::vec3(0, 0, -2);
    const auto planeNormal = glm::vec3(0, 0, 1);
    const auto wall = Plane(WHITE, AVERAGE_ALBEDO, planeOrigin, planeNormal, 1);

    // Player is looking directly at the wall
    const auto eyeOrigin = glm::vec3(0,0,0);
    const auto eyeDirection = glm::vec3(0, 0, -1);
    const auto eyeRay = Ray(eyeOrigin, eyeDirection, 0);

    auto scalar = wall.getIntersectionScalarForRay(eyeRay);
    REQUIRE_MESSAGE(scalar > 0, "Should be positive as face is intersecting");
}

TEST_CASE("Eye is above plane looking straight down") {
    const auto planeOrigin = glm::vec3(0, 0, 0);
    const auto planeNormal = glm::vec3(0, 1, 0);
    const auto wall = Plane(WHITE, AVERAGE_ALBEDO, planeOrigin, planeNormal, 1);

    const auto eyeOrigin = glm::vec3(0, 0, 0);
    const auto eyeDirection = glm::vec3(0, 1, 0);
    auto eyeRay = Ray(eyeOrigin, eyeDirection, 0);
    auto scalar = wall.getIntersectionScalarForRay(eyeRay);
            REQUIRE_MESSAGE(scalar > 0, "Scalar should be unsigned zero");
}

TEST_CASE("Plane is behind player, not visible, but normal is pointing in -Z direction") {
    const auto planeOrigin = glm::vec3(0, 0, -2);
    const auto planeNormal = glm::vec3(0, 0, -1);
    const auto wall = Plane(WHITE, AVERAGE_ALBEDO, planeOrigin, planeNormal, 1);

    const auto eyeOrigin = glm::vec3(0);
    const auto eyeDirection = glm::vec3(0, 0, -1);
    auto eyeRay = Ray(eyeOrigin, eyeDirection, 0);
    auto scalar = wall.getIntersectionScalarForRay(eyeRay);
    REQUIRE_MESSAGE(scalar < 0, "Scalar should be unsigned zero");
}

TEST_CASE("SEVDALIZA") {
    const auto eye = glm::vec3(0,0,-1);
    const auto plane = glm::vec3(0,0,1);
    const auto crossA = glm::cross(eye, plane);
    const auto crossB = glm::cross(-eye, -plane);

    REQUIRE(crossA == crossB);
}
 */
