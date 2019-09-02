//
// ray.h
// Author: Samuel Vargas
// Date: 08/11/2019
//

#pragma once
#include <glm/glm.hpp>

class Ray {
public:
    glm::vec3 origin;
    glm::vec3 direction;
    unsigned int depth;
    Ray(const glm::vec3& origin, const glm::vec3& direction, unsigned int depth);
    Ray(const glm::vec3& origin, const glm::vec3& direction);
    Ray& operator=(const Ray& other) noexcept = default;
    [[nodiscard]] glm::vec3 pointWithScalar(const float& t) const;
};
