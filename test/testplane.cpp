//
// testplane.cpp
// Author: Samuel Vargas
// Date: 08/25/2019
//

#include <doctest/doctest.h>
#include <map>
#include "color.h"
#include "plane.h"
#include "albedo.h"

TEST_CASE("Plane::getIntersectionScalarForRay(…)") {

    const auto opaqueWhite = Material(WHITE, AVERAGE_ALBEDO, MaterialType::Diffuse, 0);
    std::map<std::string, linalg::vec<float,3>> eyeDirections =  {
        {"forward", linalg::aliases::float3(0, 0, -1)},
        {"behind",  linalg::aliases::float3(0, 0, 1)},
        {"left",    linalg::aliases::float3(-1, 0, 0)},
        {"right",   linalg::aliases::float3(1, 0, 0)},
        {"top",     linalg::aliases::float3(0, 1, 0)},
        {"bottom",  linalg::aliases::float3(0, -1, 0)}
    };

    SUBCASE("Eye looking at each plane in a box triggers a collision") {
        for (const auto& direction : eyeDirections) {
            const auto planeOrigin = direction.second;
            const auto planeNormal = direction.second * -1.0f;
            const auto eyeRay = Ray(linalg::vec<float,3>(), direction.second);
            const auto plane = Plane(planeOrigin, planeNormal, opaqueWhite);
            REQUIRE_MESSAGE(plane.getIntersectionScalarForRay(eyeRay) > 0, "Face: " + direction.first);
        }
    }

    SUBCASE("Plane is in front of eye, but eye direction and plane normal are the same, no collisions should occur") {
        for (const auto& direction : eyeDirections) {
            const auto planeOrigin = direction.second; // Planes stay in the same location, but their normals are
            const auto planeNormal = direction.second; // NOT inverted anymore, and should not be visible.
            const auto eyeRay = Ray(linalg::vec<float,3>(), direction.second);
            const auto plane = Plane(planeOrigin, planeNormal, opaqueWhite);
            REQUIRE_MESSAGE(plane.getIntersectionScalarForRay(eyeRay) < 0, "Face: " + direction.first);
        }
    }

    SUBCASE("Plane is behind eye, AND plane is facing away from eye") {
        for (const auto& direction : eyeDirections) {
            const auto planeOrigin = direction.second;
            const auto planeNormal = direction.second;
            const auto eyeRay = Ray(linalg::vec<float,3>(), direction.second * -1.0f);
            const auto plane = Plane(planeOrigin, planeNormal, opaqueWhite);
            REQUIRE_MESSAGE(plane.getIntersectionScalarForRay(eyeRay) < 0, "Face: " + direction.first);
        }
    }
}
