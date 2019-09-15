//
// raycollision.h
// Author: Samuel Vargas
// Date: 08/25/2019
//

#pragma once
#include "ray.h"
#include "geometry.h"
#include <optional>
#include <memory>

struct RayCollision {
    Ray ray;
    linalg::vec<float,3> intersectionPoint;
    std::optional<std::shared_ptr<Geometry>> hitObject;
    bool isReflectedRay = false;

    RayCollision(const Ray& ray, const linalg::vec<float,3>& intersectionPoint) :
            ray(ray), intersectionPoint(intersectionPoint), hitObject(std::nullopt) {
    }

    RayCollision(const Ray& ray, const linalg::vec<float,3>& intersectionPoint, const std::shared_ptr<Geometry>& hitObject) :
        ray(ray), intersectionPoint(intersectionPoint), hitObject(std::optional<std::shared_ptr<Geometry>>(hitObject)) {
    }

    RayCollision& operator=(const RayCollision& other) noexcept {
        this->ray = other.ray;
        this->hitObject = other.hitObject;
        this->intersectionPoint = other.intersectionPoint;
        this->isReflectedRay = other.isReflectedRay;
        return *this;
    }

    linalg::vec<float,3> getSurfaceNormal() const {
        if (hitObject == std::nullopt) {
            throw std::runtime_error("No geometry found!");
        }
        return hitObject.value()->getSurfaceNormal(intersectionPoint);
    }
};

