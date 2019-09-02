//
// testrgbimage.cpp
// Author: Samuel Vargas
// Date: 08/10/2019
//

#include <doctest/doctest.h>
#include "rgbimage.h"

TEST_CASE("References to Pixels in forEachPixel loop are mutable") {
    auto onePixelImage = RGBImage(1, 1);
    const auto setToWhite = [](GLubyte& r, GLubyte& g, GLubyte& b, unsigned int row, unsigned int col) -> void {
        r = 255; g = 255; b = 255;
    };

    auto& oldBytes = onePixelImage.getRGBData();
    REQUIRE(oldBytes[0] == 0);
    REQUIRE(oldBytes[1] == 0);
    REQUIRE(oldBytes[2] == 0);
    onePixelImage.forEachPixel(setToWhite);
    REQUIRE(oldBytes[0] == 255);
    REQUIRE(oldBytes[1] == 255);
    REQUIRE(oldBytes[2] == 255);
}

TEST_CASE("X / Y Pixel in Lambda are correct") {
    auto onePixelImage = RGBImage(4, 2);
    int index = 0;
    auto expectedX = std::vector<GLuint> { 0, 1, 2, 3, 0, 1, 2, 3};
    auto expectedY = std::vector<GLuint> { 0, 0, 0, 0, 1, 1, 1, 1};

    onePixelImage.forEachPixel([&](GLubyte& r, GLubyte& g, GLubyte& b, unsigned int x, unsigned int y) -> void {
        REQUIRE(expectedX[index] == x);
        REQUIRE(expectedY[index] == y);
        ++index;
    });

}
