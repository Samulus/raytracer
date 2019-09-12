//
// raytracer.h
// Author: Samuel Vargas
// Date: 08/25/2019
//

#pragma once

#include "rgbimage.h"
#include "world.h"
#include "ray.h"
#include "lighttransport.h"

class RayTracer {
private:
    RGBImage& rgbImage;
    const World& world;
    const LightTransport& lightTransport;
    const glm::mat4 translation;
public:
    RayTracer(RGBImage& rgbImage,
              const World& world,
              const LightTransport& lightTransport);

    RayTracer(RGBImage& rgbImage,
              const World& world,
              const LightTransport& lightTransport,
              const glm::mat4& translation);

    void generateImage();
    RayCollision findNearestRayCollision(const Ray& ray);
private:
    static void
    generateSkyPixel(GLubyte& r, GLubyte& g, GLubyte& b, const unsigned int& row, const unsigned int& maxRows);
};
