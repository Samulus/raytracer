//
// lighttransport.h
// Author: Samuel Vargas
// Date: 08/25/2019
//

#pragma once
#include <GL/glew.h>
#include "raycollision.h"
#include "geometry.h"
#include "world.h"
#include "ray.h"
#include <optional>

class LightTransport {
public:
    LightTransport();
    virtual ~LightTransport() = 0;
    virtual std::optional<RayCollision>
    calculatePixelColor(GLubyte& r, GLubyte& g, GLubyte& b, const RayCollision& rayCollision, const World& world)
            const = 0;
};
