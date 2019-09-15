//
// lerp.cpp
// Author: Samuel Vargas
// Date: 08/10/2019
//

#include "lerp.h"
linalg::vec<float,3> lerp(linalg::vec<float,3> x, linalg::vec<float,3> y, float t) {
    return x * (1.f - t) + y * t;
}
