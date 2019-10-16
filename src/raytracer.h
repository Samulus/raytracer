//
// raytracer.h
// Author: Samuel Vargas
// Date: 08/25/2019
//

#pragma once

#include <algorithm>
#include "rgbimagethreaded.h"
#include "rgbimage.h"
#include "world.h"
#include "ray.h"
#include "lighttransport.h"

namespace FunctionalRayTracer {
    std::vector<Ray> generatePrimaryRaysForScene(size_t maxWidth, size_t maxHeight, uint8_t fovDegrees);

    // take (maxWidth, maxHeight) ->
    // stream of rays ->
    // stream of collided of collided objects OR nothing ->
    // if collidedObject present then lightTransport.calculatePixelColor otherwise bg color
    // result -> rgba byte data
}

class RayTracer {
private:
    RGBImage& rgbImage;
    const World& world;
    const LightTransport& lightTransport;
    const linalg::mat<float, 4,4> translation;
public:
    RayTracer(RGBImage& rgbImage,
              const World& world,
              const LightTransport& lightTransport);

    RayTracer(RGBImage& rgbImage,
              const World& world,
              const LightTransport& lightTransport,
              const linalg::mat<float,4,4>& translation);

    void generateImage();
    RayCollision findNearestRayCollision(const Ray& ray);
private:
    static void
    generateSkyPixel(GLubyte& r, GLubyte& g, GLubyte& b, const unsigned int& row, const unsigned int& maxRows);
};
