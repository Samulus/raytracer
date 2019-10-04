//
// lerp.cpp
// Author: Samuel Vargas
// Date: 08/10/2019
//

#include "lerp.h"
linalg::aliases::float3 lerp(linalg::aliases::float3 x, linalg::aliases::float3 y, float t) {
    return x * (1.f - t) + y * t;
}
