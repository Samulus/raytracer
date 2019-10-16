//
// testraytracer.cpp
// Author: Samuel Vargas 
// Date: 08/25/2019
//

#include <doctest/doctest.h>
#include "world.h"
#include "color.h"
#include "albedo.h"
#include "sphere.h"
#include "rgbimagethreaded.h"
#include "diffuselighting.h"
#include "raytracer.h"
#include "linalg.h"
using namespace linalg::ostream_overloads;

// New Functional Impl
TEST_CASE("Primary Ray Generation is OK for 3x3 px scene") {
    const auto imageWidthPx = 3;
    const auto imageHeightPx = 3;
    const auto totalPx = imageWidthPx * imageHeightPx;
    const auto fovDegrees = 50;

    auto primaryRays = FunctionalRayTracer::generatePrimaryRaysForScene(imageWidthPx, imageHeightPx, fovDegrees);

    REQUIRE_EQ(primaryRays.size(), totalPx);

    for (auto& r : primaryRays) {
        REQUIRE_EQ(linalg::aliases::float3(), r.origin);
        REQUIRE_EQ(0, r.depth);
    }

    // Expected Polarity of each primary ray for 3x3 image
    // ----------------------------
    // | -x, +y | 0, +y  | +x  +y |
    // ----------------------------
    // | -x  0  | 0   0  | +x   0 |
    // ----------------------------
    // | -x -y  | 0  -y  | +x  -y |
    // ----------------------------


    // Top row
    const auto& r = primaryRays;
    REQUIRE(r[0].direction.x < 0);
    REQUIRE(r[0].direction.y > 0);
    REQUIRE(r[0].direction.z == doctest::Approx(0));

}

// Old Impl
TEST_CASE("Sphere behind another sphere is NOT reported as the nearest sphere.") {
    auto world = World();
    const auto OPAQUE_WHITE = Material(WHITE, AVERAGE_ALBEDO, MaterialType::Diffuse, 0.0f);

    const auto closestSphere = std::make_shared<Sphere>(Sphere(linalg::vec<float,3>(0, 0, -1), 1.0f, OPAQUE_WHITE));
    const auto furtherSphere = std::make_shared<Sphere>(Sphere(linalg::vec<float,3>(0, 0, -1.1f), 1.0f, OPAQUE_WHITE));

    world.addGeometry(closestSphere);
    world.addGeometry(furtherSphere);

    auto lightTransportAlgorithm = DiffuseLighting();
    auto image = RGBImageThreaded(1, 0,0);
    auto rayTracer = RayTracer(image, world, lightTransportAlgorithm);

    const auto eyePosition = linalg::vec<float,3>();
    const auto eyeToFurtherSphere = linalg::vec<float,3>(0, 0, -1.1f) - eyePosition;

    const auto rayLookingAtFurtherSphere = Ray(eyePosition, eyeToFurtherSphere);
    const auto rayCollision = rayTracer.findNearestRayCollision(rayLookingAtFurtherSphere);

    REQUIRE_MESSAGE(rayCollision.hitObject != std::nullopt, "No collision found!");
    REQUIRE(rayCollision.hitObject == closestSphere);
}

