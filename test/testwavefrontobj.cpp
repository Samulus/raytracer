//
// testwavefrontobj.cpp
// Author: Samuel Vargas 
// Date: 09/01/2019
//

#include <doctest/doctest.h>
#include <wavefrontobj.h>
#include "material.h"
#include "meshinstance.h"
#include <iostream>

static const char* ONE_METER_CUBE_TEXT =
#include "cube.obj"
;

static const auto ONE_METER_CUBE_DATA = std::make_shared<WavefrontObj>(WavefrontObj(ONE_METER_CUBE_TEXT));

TEST_CASE("Each face reports scalar intersection") {
    const auto meshInstance = MeshInstance(glm::vec3(0), OPAQUE_DIFFUSE_RED, ONE_METER_CUBE_DATA);

    const auto ray = Ray(glm::vec3(0), glm::vec3(0, 0, -1));
    meshInstance.getIntersectionScalarForRay(ray);
    std::cout << "test" << std::endl;
}
