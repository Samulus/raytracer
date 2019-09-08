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
#include "rgbimage.h"
#include "diffuselighting.h"
#include "raytracer.h"

TEST_CASE("Sphere behind another sphere is NOT reported as the nearest sphere.") {
    auto world = World();
    const auto OPAQUE_WHITE = Material(WHITE, AVERAGE_ALBEDO, MaterialType::Diffuse, 0);

    const auto closestSphere = std::make_shared<Sphere>(Sphere(glm::vec3(0, 0, -1), 1, OPAQUE_WHITE));
    const auto furtherSphere = std::make_shared<Sphere>(Sphere(glm::vec3(0, 0, -1.1), 1, OPAQUE_WHITE));

    world.addGeometry(closestSphere);
    world.addGeometry(furtherSphere);

    auto lightTransportAlgorithm = DiffuseLighting();
    auto image = RGBImage(0,0);
    auto rayTracer = RayTracer(image, world, lightTransportAlgorithm);

    const auto eyePosition = glm::vec3();
    const auto eyeToFurtherSphere = glm::vec3(0, 0, -1.1) - eyePosition;

    const auto rayLookingAtFurtherSphere = Ray(eyePosition, eyeToFurtherSphere);
    const auto rayCollision = rayTracer.findNearestRayCollision(rayLookingAtFurtherSphere);

    REQUIRE_MESSAGE(rayCollision.hitObject != std::nullopt, "No collision found!");
    REQUIRE(rayCollision.hitObject == closestSphere);
}

