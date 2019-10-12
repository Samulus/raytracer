//
// testdiffuselighting.cpp
// Author: Samuel Vargas
// Date: 08/25/2019
//

#include <doctest/doctest.h>
#include <diffuselighting.h>
#include <triangle.h>
#include <linalg.h>
#include "albedo.h"
#include "color.h"
#include "plane.h"

static const auto OPAQUE_WHITE = Material(WHITE, AVERAGE_ALBEDO, MaterialType::Diffuse, 0); // NOLINT(cert-err58-cpp)

TEST_CASE("Ray casted from point on plane directly below sphere results in a collision") {
    const auto sphereOrigin = linalg::vec<float,3>(0, 2, -4);
    const auto sphereRadius = 0.1f;
    const auto sphereMaterial = OPAQUE_WHITE;
    const auto planeOrigin = linalg::vec<float,3>(0, 0, 0);
    const auto planeNormal = linalg::vec<float,3>(0, 1, 0);
    const auto planeMaterial = OPAQUE_WHITE;
    const auto sunDirection = linalg::vec<float,3>(0, -1, 0);
    const auto sunIntensity = 20.0f;
    const auto sunColor = WHITE;

    std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(Sphere(sphereOrigin, sphereRadius, sphereMaterial));
    std::shared_ptr<Plane> plane = std::make_shared<Plane>(Plane(planeOrigin, planeNormal, planeMaterial));
    std::unique_ptr<Light> sun = std::make_unique<SunLight>(SunLight(sunDirection, WHITE, sunIntensity));
    auto world = World();
    auto diffuseLighting = DiffuseLighting();
    world.addGeometry(sphere);
    world.addGeometry(plane);
    diffuseLighting.addLight(sun);

    auto pointUnderSphere = sphereOrigin;
    pointUnderSphere.y = planeOrigin.y;

    const auto rayFromSpotUnderSphereOnPlaneIntoPlane = Ray(pointUnderSphere, planeNormal);
    const auto rayCollision = world.rayIntersectionTest(
            rayFromSpotUnderSphereOnPlaneIntoPlane,
            Universe::MaximumViewDistance
    );

    REQUIRE(rayCollision != std::nullopt);
    REQUIRE(rayCollision->hitObject == sphere);
    REQUIRE(rayCollision->intersectionPoint.x == sphereOrigin.x);
    REQUIRE(rayCollision->intersectionPoint.y == doctest::Approx(sphereOrigin.y - sphereRadius));
}

TEST_CASE("Sole plane is illuminated by extremely bright light") {
    const auto planeOrigin = linalg::vec<float,3>(0, 0, 0);
    const auto planeNormal = linalg::vec<float,3>(0, 1, 0);
    const auto planeMaterial = OPAQUE_WHITE;
    const auto sunPosition = linalg::vec<float,3>(0, Universe::MaximumViewDistance - 1, -3);
    const auto sunDirection = linalg::vec<float,3>(0, -1, 0);
    const auto sunIntensity = 1000.0f;
    const auto sunColor = WHITE;

    auto plane = std::make_shared<Plane>(Plane(planeOrigin, planeNormal, planeMaterial));
    std::unique_ptr<Light> sun = std::make_unique<SunLight>(SunLight(sunDirection, WHITE, sunIntensity));

    auto world = World();
    auto diffuseLighting = DiffuseLighting();
    world.addGeometry(plane);
    diffuseLighting.addLight(sun);

    GLubyte r = 0;
    GLubyte g = 0;
    GLubyte b = 0;

    // Simulate a ray in front of us is illuminating  the floor
    const auto eyePlaneIntersectionPoint = linalg::vec<float,3>(0, 0, -3);
    const auto eyeDirection = eyePlaneIntersectionPoint - Universe::HumanEyeOrigin;
    const auto eyeToPointOnPlane = Ray(Universe::HumanEyeOrigin, linalg::normalize(eyeDirection));
    const auto sunRayCollision = RayCollision(eyeToPointOnPlane, eyePlaneIntersectionPoint, plane);

    diffuseLighting.calculatePixelColor(r, g, b, sunRayCollision, world);

    REQUIRE(r == 255);
    REQUIRE(g == 255);
    REQUIRE(b == 255);
}

//                             (0, 0, -1)
//                                 /\
//   Triangle Normal:             /  \
//      (0, 1, 0)                /    \
//                              /      \
//   Triangle color is         / [PL]   \
//      WHITE                 /  ____    \
//                           /  /    \    \
//                          /  |      |.................. (0.5, 0.2, -0.5), radius = 0.1m, bottom of sphere has 10cm
//                         /    \____/      \                                              gap between itself and
//                        /      ****...........................                           triangle.
//                       /        **          \                ......... Should be BLACK.
//         (-1, 0, 0)   /______________________\ (1, 0, 0)
//
//

TEST_CASE("Point Light over Sphere over Triangle Casts Shadow on Triangle") {
    static const auto OPAQUE_RED = Material(RED, AVERAGE_ALBEDO, MaterialType::Diffuse, 0);
    auto world = World();
    auto diffuseLighting = DiffuseLighting();

    std::unique_ptr<Light> light =
            std::make_unique<PointLight>(PointLight(linalg::vec<float,3>(0, 1, -0.5), WHITE, 100.0f));

    diffuseLighting.addLight(light);

    const linalg::vec<float,3> v0 = linalg::vec<float,3>(0, 0, -1);
    const linalg::vec<float,3> v1 = linalg::vec<float,3>(-1, 0, 0);
    const linalg::vec<float,3> v2 = linalg::vec<float,3>(1, 0, 0);
    const linalg::vec<float,3> normal = linalg::vec<float,3>(0, 1, 0);

    const auto sphereOrigin = linalg::vec<float,3>(0.5f, 0.2f, -0.5f);

    const std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(Sphere(sphereOrigin, 0.1f, OPAQUE_RED));
    const std::shared_ptr<Triangle> triangle = std::make_shared<Triangle>(Triangle(v0, v1, v2, normal, OPAQUE_WHITE));

    world.addGeometry(sphere);
    world.addGeometry(triangle);

    // Create a ray starting 1cm under the sphere pointing down and into the triangle below,
    // it should be in the shadow.
    auto rayOrigin = linalg::vec<float,3>(sphereOrigin);
    rayOrigin.y = sphereOrigin.y - 0.01f;
    const auto ray = Ray(rayOrigin, linalg::vec<float,3>(0, -1, 0));
    auto triangleIntersectionPoint = linalg::vec<float,3>(sphereOrigin);
    triangleIntersectionPoint.y = v0.y;
    const auto shadowRay = RayCollision(ray, triangleIntersectionPoint, triangle);

    GLubyte r = 255;
    GLubyte g = 255;
    GLubyte b = 255;

    diffuseLighting.calculatePixelColor(r, g, b, shadowRay, world);

    REQUIRE(r == 0);
    REQUIRE(g == 0);
    REQUIRE(b == 0);
}
