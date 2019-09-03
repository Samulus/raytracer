//
// ray.cpp
// Author: Samuel Vargas
// Date: 08/11/2019
//

#include "ray.h"

Ray::Ray(const glm::vec3& origin, const glm::vec3& direction, unsigned int depth)
        : origin(origin), direction(glm::normalize(direction)), depth(depth) {
}

Ray::Ray(const glm::vec3& origin, const glm::vec3& direction)
        : origin(origin), direction(glm::normalize(direction)), depth(0) {
}

Ray::~Ray() = default;

Ray& Ray::operator=(const Ray& other) = default;

glm::vec3 Ray::pointWithScalar(float t) const {
    return origin + (t * direction);
}
