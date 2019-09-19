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
    const linalg::aliases::float3 color;
    const linalg::aliases::float3 albedo;
    const float reflectiveness;
    const MaterialType materialType;
    Material(linalg::aliases::float3 color, linalg::aliases::float3 albedo, MaterialType materialType, float reflectiveness) :
        color(color), albedo(albedo), materialType(materialType), reflectiveness(reflectiveness) {
    }
};

