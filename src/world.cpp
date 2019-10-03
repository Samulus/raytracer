//
// world.cpp
// Author: Samuel Vargas
// Date: 08/25/2019
//

#include "world.h"
#include "sphere.h"

void World::addGeometry(const std::shared_ptr<Geometry>& item) {
    geometry.emplace_back(item);
}

std::vector<std::shared_ptr<Geometry>> World::getGeometry() const {
    return geometry;
}

std::optional<RayCollision> World::rayIntersectionTest(const Ray& ray, float maxScalarDistance) const {
    for (const auto& currentGeometry : geometry) {
        const auto intersectionScalar = currentGeometry->getIntersectionScalarForRay(ray);
        const auto isOccluded = intersectionScalar > 0 && intersectionScalar < maxScalarDistance;

        if (isOccluded) {
            auto result = RayCollision(ray, ray.pointWithScalar(intersectionScalar), currentGeometry);
            return std::optional<RayCollision>(result);
        }
    }

    return std::nullopt;
}