//
// mollertumbore.h
// Author: Samuel Vargas 
// Date: 09/02/2019
//

#pragma once

#include <glm/glm.hpp>
#include "ray.h"

glm::vec3 getNormalForTriangle(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2);

bool isEyeInFrontOfPlane(const Ray& ray, const glm::vec3& arbitraryPlanePoint);

bool pointIsInsideTheTriangle(
        const glm::vec3& p,
        const glm::vec3& n,
        const glm::vec3& v0,
        const glm::vec3& v1,
        const glm::vec3& v2);

float isRayIntersectingTriangle(
        const Ray& ray,
        const glm::vec3& v0,
        const glm::vec3& v1,
        const glm::vec3& v2,
        bool isSingleSided = true);

float mollertrumboreIntersection(
        const Ray& ray,
        const glm::vec3& v0,
        const glm::vec3& v1,
        const glm::vec3& v2,
        const glm::vec3& normal);

