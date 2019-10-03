//
// world.h
// Author: Samuel Vargas
// Date: 08/25/2019
//

#pragma once
#include <vector>
#include <functional>
#include <memory>
#include "raycollision.h"
#include "sphere.h"
#include "light.h"

class World {
private:
    std::vector<std::shared_ptr<Geometry>> geometry;
public:
    explicit World() = default;
    void addGeometry(const std::shared_ptr<Geometry>& geometry);
    [[ nodiscard ]] std::vector<std::shared_ptr<Geometry>> getGeometry() const;
    [[nodiscard]] std::optional<RayCollision> rayIntersectionTest(const Ray& ray, float maxScalarDistance) const;
};
