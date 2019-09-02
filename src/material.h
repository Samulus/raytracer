//
// material.h
// Author: Samuel Vargas
// Date: 08/25/2019
//

#pragma once
#include <glm/glm.hpp>
#include "albedo.h"
#include "color.h"

enum MaterialType {
    Diffuse,
    Reflective
};

struct Material {
    const glm::vec3 color;
    const glm::vec3 albedo;
    // TODO: This is unused
    const float reflectiveness;
    const MaterialType materialType;
    Material(glm::vec3 color, glm::vec3 albedo, MaterialType materialType, float reflectiveness) :
        color(color), albedo(albedo), materialType(materialType), reflectiveness(reflectiveness) {
    }
};

static const auto OPAQUE_DIFFUSE_RED = Material(RED, AVERAGE_ALBEDO, MaterialType::Diffuse, 0);
