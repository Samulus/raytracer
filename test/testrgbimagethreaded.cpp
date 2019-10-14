//
// testrgbimagethreaded.cpp
// Author: Samuel Vargas
// Date: 08/10/2019
//

#include <doctest/doctest.h>
#include <vector>
#include <spdlog/spdlog.h>
#include "gl_glfw.h"
#include "rgbimagethreaded.h"

const auto setPixelToWhite = [](GLubyte& r, GLubyte& g, GLubyte& b, unsigned int x, unsigned int y) -> void {
    r = 255;
    g = 255;
    b = 255;
};

TEST_CASE("Smoke Test for rgbimagethread") {
    auto threePixelImage = RGBImageThreaded(3, 3, 3);
    const auto& oldBytes = std::vector<GLubyte>(threePixelImage.getPixelData());
    REQUIRE_EQ(false, threePixelImage.isImageBeingGenerated());
    REQUIRE_EQ(3 * 3 * 3, oldBytes.size());
    for (GLubyte b : oldBytes) {
        REQUIRE_EQ(0, b);
    }

    threePixelImage.forEachPixelInParallel(setPixelToWhite);

    while (threePixelImage.isImageBeingGenerated()) {
        //spdlog::info("Spinning");
        // spinlock
    }

    const auto newBytes = threePixelImage.getPixelData();
    for (GLubyte b : newBytes) {
        REQUIRE_EQ(255, b);
    }

}
