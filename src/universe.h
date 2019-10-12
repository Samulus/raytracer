//
// universe.h
// Author: Samuel Vargas
// Date: 08/31/2019
//

#pragma once
#include <limits>
#include <linalg.h>

namespace Universe {
    static constexpr float MaximumViewDistance = 100.0f;
    static constexpr float HumanEyeLevel = 1.8288f;
    static constexpr linalg::aliases::float3 HumanEyeOrigin = linalg::vec<float,3>(0, HumanEyeLevel, 0);
}