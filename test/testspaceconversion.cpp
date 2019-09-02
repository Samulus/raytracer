//
// testspaceconversion.cpp
// Author: Samuel Vargas
// Date: 08/25/2019
//

#include <doctest/doctest.h>
#include <universe.h>
#include <glm/ext/matrix_transform.hpp>
#include "spaceconversion.h"


TEST_CASE("Verify Raster → NDC Coordinate Conversion") {
    auto ndc = SpaceConversion::rasterToNdc(1,0, 3, 2);
    REQUIRE(ndc.x == doctest::Approx(0.5));
    REQUIRE(ndc.y == doctest::Approx(0.25));
}

TEST_CASE("Verify primary rays are correct") {
    auto ndcCoordinates = SpaceConversion::rasterToNdc(1, 1, 3, 3);
    REQUIRE(ndcCoordinates.x == doctest::Approx(0.5));
    REQUIRE(ndcCoordinates.y == doctest::Approx(0.5));

    auto screenSpace = SpaceConversion::ndcToScreen(ndcCoordinates);
    REQUIRE(screenSpace.x == doctest::Approx(0));
    REQUIRE(screenSpace.y == doctest::Approx(0));

    auto cameraSpace = SpaceConversion::screenToCamera(screenSpace, 3.0f/3.0f, 90.0f);
    REQUIRE(cameraSpace.x == doctest::Approx(0.0f));
    REQUIRE(cameraSpace.y == doctest::Approx(0.0f));
}

TEST_CASE("Primary ray translated to eye origin is correct") {
    const auto eyeTranslationMatrix = glm::translate(glm::mat4(1), Universe::HumanEyeOrigin);
    const auto nonTranslatedRay = SpaceConversion::pixelToPrimaryRay(1, 1, 3, 3, 50.0f);

    // If looking in the center of the screen
    REQUIRE(nonTranslatedRay.origin.x == 0);
    REQUIRE(nonTranslatedRay.origin.y == 0);
    REQUIRE(nonTranslatedRay.origin.z == 0);
    REQUIRE(nonTranslatedRay.direction.x == 0);
    REQUIRE(nonTranslatedRay.direction.y == 0);
    REQUIRE(nonTranslatedRay.direction.z == -1);

    // If looking in the center of the scree

}

