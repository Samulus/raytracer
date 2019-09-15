//
// material.h
// Author: Samuel Vargas
// Date: 08/25/2019
//

#pragma once
#include "albedo.h"
#include "color.h"

enum MaterialType {
    Diffuse,
    Reflective
};

struct Material {
    const linalg::vec<float,3> color;
    const linalg::vec<float,3> albedo;
    // TODO: This is unused
    const float reflectiveness;
    const MaterialType materialType;
    Material(linalg::vec<float,3> color, linalg::vec<float,3> albedo, MaterialType materialType, float reflectiveness) :
        color(color), albedo(albedo), materialType(materialType), reflectiveness(reflectiveness) {
    }
};

static const auto OPAQUE_DIFFUSE_RED = Material(RED, AVERAGE_ALBEDO, MaterialType::Diffuse, 0);
