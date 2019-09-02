//
// diffuselighting.cpp
// Author: Samuel Vargas
// Date: 08/23/2019
//

#include "diffuselighting.h"
#include "spaceconversion.h"
#include <algorithm>
static float SHADOW_BIAS = 1e-4;
DiffuseLighting::~DiffuseLighting() = default;
std::optional<RayCollision>
DiffuseLighting::calculatePixelColor(GLubyte& r, GLubyte& g, GLubyte& b, const RayCollision& rayCollision,
                                     const World& world) const {
    if (rayCollision.hitObject == std::nullopt) {
        throw std::runtime_error("DiffuseLighting::calculatePixelColor(…) invoked with a rayCollision missing an obj!");
    }
    const auto materialType = rayCollision.hitObject.value()->getMaterial().materialType;
    const auto primaryRay = rayCollision.ray;
    if (materialType == MaterialType::Diffuse) {
        calculateDiffuseColor(r, g, b, rayCollision, world);
        return std::nullopt;
    }
    if (materialType == MaterialType::Reflective) {
        const auto& surfaceNormal = rayCollision.getSurfaceNormal();
        const auto& reflectedDirection =
                primaryRay.direction - 2.0f * glm::dot(primaryRay.direction, surfaceNormal) * surfaceNormal;
        const auto& reflectRayOrigin = rayCollision.intersectionPoint + (surfaceNormal * SHADOW_BIAS);
        const auto& newRayDirection = reflectedDirection;
        const auto& reflectionRay = Ray(reflectRayOrigin, reflectedDirection, primaryRay.depth + 1);
        auto newRayCollision = RayCollision(reflectionRay, rayCollision.intersectionPoint);
        newRayCollision.isReflectedRay = true;
        return std::optional<RayCollision>(newRayCollision);
    }
    assert(false);
    return std::nullopt;
}
void DiffuseLighting::calculateDiffuseColor(
        GLubyte& r,
        GLubyte& g,
        GLubyte& b,
        const RayCollision& rayCollision,
        const World& world
) const {
    const auto& hitObject = rayCollision.hitObject.value();
    const auto& intersectionPoint = rayCollision.intersectionPoint;
    const auto& surfaceNormal = hitObject->getSurfaceNormal(intersectionPoint);
    auto finalColor = glm::vec3();
    for (const auto& light : lights) {
        auto inverseLightDirection = light->getInverseLightDirection(intersectionPoint);
        const auto distanceToLight = light->getDistanceFromLightToIntersectionPoint(intersectionPoint);

        // Shadow Detection
        const auto occlusionRay = Ray(intersectionPoint + (surfaceNormal * SHADOW_BIAS), inverseLightDirection);
        if (rayIntersectsAnyGeometry(occlusionRay, world, distanceToLight) != std::nullopt) {
            r = 0;
            g = 0;
            b = 0;
            return;
        }
        finalColor += calculateLightContribution(light.get(), intersectionPoint, hitObject.get());
    }
    r = std::clamp(finalColor.r * 255.0f, 0.0f, 255.0f);
    g = std::clamp(finalColor.g * 255.0f, 0.0f, 255.0f);
    b = std::clamp(finalColor.b * 255.0f, 0.0f, 255.0f);
}
void DiffuseLighting::addLight(std::unique_ptr<Light> light) {
    lights.emplace_back(std::move(light));
}
std::optional<RayCollision>
DiffuseLighting::rayIntersectsAnyGeometry(const Ray& occlusionRay, const World& world, float maxScalarDistance) const {
    for (const auto& currentGeometry : world.getGeometry()) {
        const auto intersectionScalar = currentGeometry->getIntersectionScalarForRay(occlusionRay);
        const auto isOccluded = intersectionScalar > 0 && intersectionScalar < maxScalarDistance;
        if (isOccluded) {
            auto result = RayCollision(occlusionRay, occlusionRay.pointWithScalar(intersectionScalar), currentGeometry);
            return std::optional<RayCollision>(result);
        }
    }
    return std::nullopt;
}
glm::vec3 DiffuseLighting::calculateLightContribution(const Light* light, const glm::vec3& intersectionPoint,
                                                      const Geometry* hitObject) const {
    auto outputColor = glm::vec3();
    auto inverseLightDirection = light->getInverseLightDirection(intersectionPoint);
    auto distanceToLight = light->getDistanceFromLightToIntersectionPoint(intersectionPoint);
    const auto& surfaceNormal = hitObject->getSurfaceNormal(intersectionPoint);
    if (light->isInfinitelyTravellingLight()) {
        outputColor = light->intensity * light->color;
        inverseLightDirection = glm::normalize(inverseLightDirection);
    } else { // Simulate falloff
        outputColor = light->intensity * light->color / (4.0f * PI * distanceToLight);
        inverseLightDirection = glm::normalize(inverseLightDirection / distanceToLight);
    }
    const auto lambertCosine = glm::dot(surfaceNormal, inverseLightDirection);
    outputColor *= hitObject->getMaterial().albedo / PI;
    outputColor *= hitObject->getMaterial().color;
    outputColor *= light->color;
    outputColor *= std::max(0.0f, lambertCosine);
    return outputColor;
}
