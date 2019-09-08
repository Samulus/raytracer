//
// testdiffuselighting.cpp
// Author: Samuel Vargas
// Date: 08/25/2019
//

#include <doctest/doctest.h>
#include <diffuselighting.h>
#include "albedo.h"
#include "color.h"
#include "plane.h"

static const auto OPAQUE_WHITE = Material(WHITE, AVERAGE_ALBEDO, MaterialType::Diffuse, 0); // NOLINT(cert-err58-cpp)

TEST_CASE("Ray casted from point on plane directly below sphere results in a collision") {
    const auto sphereOrigin = glm::vec3(0, 2, -4);
    const auto sphereRadius = 0.1;
    const auto sphereMaterial = OPAQUE_WHITE;
    const auto planeOrigin = glm::vec3(0, 0, 0);
    const auto planeNormal = glm::vec3(0, 1, 0);
    const auto planeMaterial = OPAQUE_WHITE;
    const auto sunDirection = glm::vec3(0, -1, 0);
    const auto sunIntensity = 20.0f;
    const auto sunColor = WHITE;

    auto sphere = std::make_shared<Sphere>(Sphere(sphereOrigin, sphereRadius, sphereMaterial));
    auto plane = std::make_shared<Plane>(Plane(planeOrigin, planeNormal, planeMaterial));
    auto sun = std::make_unique<SunLight>(SunLight(sunDirection, WHITE, sunIntensity));
    auto world = World();
    auto diffuseLighting = DiffuseLighting();
    world.addGeometry(sphere);
    world.addGeometry(plane);
    diffuseLighting.addLight(std::move(sun));

    auto pointUnderSphere = sphereOrigin;
    pointUnderSphere.y = planeOrigin.y;

    const auto rayFromSpotUnderSphereOnPlaneIntoPlane = Ray(pointUnderSphere, planeNormal);
    const auto rayCollision = diffuseLighting.rayIntersectsAnyGeometry(
            rayFromSpotUnderSphereOnPlaneIntoPlane,
            world,
            Universe::MaximumViewDistance
    );

    REQUIRE(rayCollision != std::nullopt);
    REQUIRE(rayCollision->hitObject == sphere);
    REQUIRE(rayCollision->intersectionPoint.x == sphereOrigin.x);
    REQUIRE(rayCollision->intersectionPoint.y == doctest::Approx(sphereOrigin.y - sphereRadius));
}

TEST_CASE("Sole plane is illuminated by extremely bright light") {
    const auto planeOrigin = glm::vec3(0, 0, 0);
    const auto planeNormal = glm::vec3(0, 1, 0);
    const auto planeMaterial = OPAQUE_WHITE;
    const auto sunPosition = glm::vec3(0, Universe::MaximumViewDistance - 1, -3);
    const auto sunDirection = glm::vec3(0, -1, 0);
    const auto sunIntensity = 1000.0f;
    const auto sunColor = WHITE;

    auto plane = std::make_shared<Plane>(Plane(planeOrigin, planeNormal, planeMaterial));
    auto sun = std::make_unique<SunLight>(SunLight(sunDirection, WHITE, sunIntensity));

    auto world = World();
    auto diffuseLighting = DiffuseLighting();
    world.addGeometry(plane);
    diffuseLighting.addLight(std::move(sun));

    GLubyte r = 0;
    GLubyte g = 0;
    GLubyte b = 0;

    // Simulate a ray in front of us is illuminating  the floor
    const auto eyePlaneIntersectionPoint = glm::vec3(0, 0, -3);
    const auto eyeDirection = eyePlaneIntersectionPoint - Universe::HumanEyeOrigin;
    const auto eyeToPointOnPlane = Ray(Universe::HumanEyeOrigin, glm::normalize(eyeDirection));
    const auto sunRayCollision = RayCollision(eyeToPointOnPlane, eyePlaneIntersectionPoint, plane);

    diffuseLighting.calculatePixelColor(r, g, b, sunRayCollision, world);

    REQUIRE(r == 255);
    REQUIRE(g == 255);
    REQUIRE(b == 255);
}