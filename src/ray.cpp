//
// ray.cpp
// Author: Samuel Vargas
// Date: 08/11/2019
//

#include "ray.h"

Ray::Ray(const linalg::vec<float,3>& origin, const linalg::vec<float,3>& direction, unsigned int depth)
        : origin(origin), direction(linalg::normalize(direction)), depth(depth) {
}

Ray::Ray(const linalg::vec<float,3>& origin, const linalg::vec<float,3>& direction)
        : origin(origin), direction(linalg::normalize(direction)), depth(0) {
}

Ray::~Ray() = default;

Ray& Ray::operator=(const Ray& other) = default;

linalg::vec<float,3> Ray::pointWithScalar(float t) const {
    return origin + (t * direction);
}
