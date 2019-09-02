//
// light.h
// Author: Samuel Vargas
// Date: 08/23/2019
//

#pragma once
#include <glm/glm.hpp>
#include <optional>
#include "universe.h"

struct Light {
    const glm::vec3 color;
    const float intensity;

    Light(glm::vec3 color, float intensity) :
        color(color), intensity(intensity) {
    }

    [[ nodiscard ]] virtual std::optional<glm::vec3> getPosition() const = 0;
    [[ nodiscard ]] virtual float getDistanceFromLightToIntersectionPoint(glm::vec3 intersectionPoint) const = 0;

    /**
     * Get the inverted light direction. This function is intended to be used in lighting calculations,
     * where `intersectionPoint` is an arbitrary point that needs to be shaded. This function will
     * return the inverse direction of the light relative to that point, so a ray can be constructed
     * for occlusion detection / shadows etc.
     *
     * Note that some lights (like `SunLight`) will ignore the intersectionPoint and return a constant
     * direction.
     */

    virtual bool isInfinitelyTravellingLight() const = 0;
    [[ nodiscard ]] virtual glm::vec3 getInverseLightDirection(const glm::vec3& intersectionPoint) const = 0;
};

struct SunLight : Light {
    glm::vec3 direction;
    SunLight(glm::vec3 direction, glm::vec3 color, float intensity) : direction(direction), Light(color, intensity) {
    }

    [[ nodiscard ]] std::optional<glm::vec3> getPosition() const override {
        return std::nullopt;
    }

    [[ nodiscard ]] float getDistanceFromLightToIntersectionPoint(glm::vec3 intersectionPoint) const override {
        return Universe::MaximumViewDistance + 1.0f;
    }

    [[ nodiscard ]] glm::vec3 getInverseLightDirection(const glm::vec3& intersectionPoint) const override {
        return -glm::normalize(direction);
    }

    [[ nodiscard ]] bool isInfinitelyTravellingLight() const override {
        return true;
    }
};

struct PointLight : Light {
    const glm::vec3 position;
    PointLight(glm::vec3 position, glm::vec3 color, float intensity) :
            position(position), Light(color, intensity) {
    }

    [[ nodiscard ]] std::optional<glm::vec3> getPosition() const override {
        return std::optional<glm::vec3>(position);
    }

    [[ nodiscard ]] float getDistanceFromLightToIntersectionPoint(glm::vec3 intersectionPoint) const override {
        const auto lightDirection = position - intersectionPoint;
        const auto distanceFromLightToIntersectionPoint = glm::sqrt(glm::length(lightDirection));
        return distanceFromLightToIntersectionPoint;
    }

    [[ nodiscard ]] glm::vec3 getInverseLightDirection(const glm::vec3& intersectionPoint) const override {
        auto inverseDirection = position - intersectionPoint;
        auto dist = glm::sqrt(glm::length(inverseDirection));
        assert(std::abs(dist) > std::numeric_limits<float>::epsilon());
        return inverseDirection / dist;
    }

    [[ nodiscard ]] bool isInfinitelyTravellingLight() const override {
        return false;
    }
};
