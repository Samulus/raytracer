//
// universe.h
// Author: Samuel Vargas
// Date: 08/31/2019
//

#pragma once
#include <limits>
#include <glm/glm.hpp>

namespace Universe {
    static constexpr auto MaximumViewDistance = 100.0f;
    static constexpr auto HumanEyeLevel = 1.8288;
    static constexpr auto HumanEyeOrigin = glm::vec3(0, HumanEyeLevel, 0);
}