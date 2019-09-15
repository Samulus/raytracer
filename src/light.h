//
// light.h
// Author: Samuel Vargas
// Date: 08/23/2019
//

#pragma once
#include <optional>
#include <cassert>
#include "universe.h"

struct Light {
    const linalg::vec<float,3> color;
    const float intensity;

    Light(linalg::vec<float,3> color, float intensity) :
        color(color), intensity(intensity) {
    }

    [[ nodiscard ]] virtual std::optional<linalg::vec<float,3>> getPosition() const = 0;
    [[ nodiscard ]] virtual float getDistanceFromLightToIntersectionPoint(linalg::vec<float,3> intersectionPoint) const = 0;

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
    [[ nodiscard ]] virtual linalg::vec<float,3> getInverseLightDirection(const linalg::vec<float,3>& intersectionPoint) const = 0;
};

struct SunLight : Light {
    linalg::vec<float,3> direction;
    SunLight(linalg::vec<float,3> direction, linalg::vec<float,3> color, float intensity) : direction(direction), Light(color, intensity) {
    }

    [[ nodiscard ]] std::optional<linalg::vec<float,3>> getPosition() const override {
        return std::nullopt;
    }

    [[ nodiscard ]] float getDistanceFromLightToIntersectionPoint(linalg::vec<float,3> intersectionPoint) const override {
        return Universe::MaximumViewDistance + 1.0f;
    }

    [[ nodiscard ]] linalg::vec<float,3> getInverseLightDirection(const linalg::vec<float,3>& intersectionPoint) const override {
        return -linalg::normalize(direction);
    }

    [[ nodiscard ]] bool isInfinitelyTravellingLight() const override {
        return true;
    }
};

struct PointLight : Light {
    const linalg::vec<float,3> position;
    PointLight(linalg::vec<float,3> position, linalg::vec<float,3> color, float intensity) :
            position(position), Light(color, intensity) {
    }

    [[ nodiscard ]] std::optional<linalg::vec<float,3>> getPosition() const override {
        return std::optional<linalg::vec<float,3>>(position);
    }

    [[ nodiscard ]] float getDistanceFromLightToIntersectionPoint(linalg::vec<float,3> intersectionPoint) const override {
        const auto lightDirection = position - intersectionPoint;
        const auto distanceFromLightToIntersectionPoint = linalg::sqrt(linalg::length(lightDirection));
        return distanceFromLightToIntersectionPoint;
    }

    [[ nodiscard ]] linalg::vec<float,3> getInverseLightDirection(const linalg::vec<float,3>& intersectionPoint) const override {
        auto inverseDirection = position - intersectionPoint;
        auto dist = linalg::sqrt(linalg::length(inverseDirection));
        assert(std::abs(dist) > std::numeric_limits<float>::epsilon());
        return inverseDirection / dist;
    }

    [[ nodiscard ]] bool isInfinitelyTravellingLight() const override {
        return false;
    }
};
