//
// universe.h
// Author: Samuel Vargas
// Date: 08/31/2019
//

#pragma once
#include <limits>
#include <linalg.h>

namespace Universe {
    static constexpr auto MaximumViewDistance = 100.0f;
    static constexpr auto HumanEyeLevel = 1.8288;
    static constexpr auto HumanEyeOrigin = linalg::vec<float,3>(0, HumanEyeLevel, 0);
}