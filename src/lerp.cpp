//
// lerp.cpp
// Author: Samuel Vargas
// Date: 08/10/2019
//

#include "lerp.h"
glm::vec3 lerp(glm::vec3 x, glm::vec3 y, float t) {
    return x * (1.f - t) + y * t;
}
