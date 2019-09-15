//
// testwavefrontobj.cpp
// Author: Samuel Vargas 
// Date: 09/01/2019
//

#include <doctest/doctest.h>
#include <wavefrontobj.h>
#include <iostream>
#include <linalg.h>
#include "material.h"
#include "meshinstance.h"

static const char* ONE_METER_CUBE_TEXT =
#include "cube.obj"
;

static const auto ONE_METER_CUBE_DATA = std::make_shared<WavefrontObj>(WavefrontObj(ONE_METER_CUBE_TEXT));

TEST_CASE("Each face reports scalar intersection") {
    const auto meshInstance = MeshInstance(linalg::vec<float,3>(), OPAQUE_DIFFUSE_RED, ONE_METER_CUBE_DATA);

    const auto ray = Ray(linalg::vec<float,3>(), linalg::vec<float,3>(0, 0, -1));
    meshInstance.getIntersectionScalarForRay(ray);
}
