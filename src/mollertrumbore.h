//
// mollertumbore.h
// Author: Samuel Vargas 
// Date: 09/02/2019
//

#pragma once

#include <optional>
#include "ray.h"

linalg::vec<float,3> getNormalForTriangle(const linalg::vec<float,3>& v0, const linalg::vec<float,3>& v1, const linalg::vec<float,3>& v2);

bool isEyeInFrontOfPlane(const Ray& ray, const linalg::vec<float,3>& arbitraryPlanePoint);

bool pointIsInsideTheTriangle(
        const linalg::vec<float,3>& p,
        const linalg::vec<float,3>& n,
        const linalg::vec<float,3>& v0,
        const linalg::vec<float,3>& v1,
        const linalg::vec<float,3>& v2);

float isRayIntersectingTriangle(
        const Ray& ray,
        const linalg::vec<float,3>& v0,
        const linalg::vec<float,3>& v1,
        const linalg::vec<float,3>& v2,
        const std::optional<linalg::vec<float,3>> normal = std::nullopt,
        bool isSingleSided = true);

float mollertrumboreIntersection(
        const Ray& ray,
        const linalg::vec<float,3>& v0,
        const linalg::vec<float,3>& v1,
        const linalg::vec<float,3>& v2,
        const linalg::vec<float,3>& normal);

