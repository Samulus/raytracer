//
// ray.cpp
// Author: Samuel Vargas
// Date: 08/11/2019
//

#include "ray.h"

Ray::Ray(const linalg::aliases::float3& origin, const linalg::aliases::float3& direction, unsigned int depth)
        : origin(origin), direction(linalg::normalize(direction)), depth(depth) {
}

Ray::Ray(const linalg::aliases::float3& origin, const linalg::aliases::float3& direction)
        : origin(origin), direction(linalg::normalize(direction)), depth(0) {
}

Ray::~Ray() = default;

Ray& Ray::operator=(const Ray& other) = default;

linalg::aliases::float3 Ray::pointWithScalar(float t) const {
    return origin + (t * direction);
}
