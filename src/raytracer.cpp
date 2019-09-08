//
// raytracer.cpp
// Author: Samuel Vargas
// Date: 08/25/2019
//

#include "raytracer.h"
#include "lerp.h"
#include "spaceconversion.h"
#include "universe.h"
#include <glm/ext/matrix_transform.hpp>

static constexpr glm::vec3 SKY_LIGHT_COLOR = glm::vec3{0.6901, 0.62745, 0.88};
static constexpr glm::vec3 SKY_DARK_COLOR = glm::vec3{0.89411, 0.69019, 0.75};
//static constexpr glm::vec3 SKY_LIGHT_COLOR = glm::vec3{0.8, 0.8, 0.8};
//static constexpr glm::vec3 SKY_DARK_COLOR = glm::vec3{0, 0.19607, 0.298039};
static int MAXIMUM_REFLECTION_RECURSION = 5;

RayTracer::RayTracer(RGBImage& rgbImage, const World& world, const LightTransport& lightTransport) :
        rgbImage(rgbImage), world(world), lightTransport(lightTransport) {
    generateImage();
}

void RayTracer::generateImage() {
    const auto maxWidth = rgbImage.getXRes();
    const auto maxHeight = rgbImage.getYRes();

    const auto eyeTranslationMatrix = glm::translate(glm::mat4(1), glm::vec3(0, 1, 1));

    rgbImage.forEachPixel(
            [&](GLubyte& r, GLubyte& g, GLubyte& b, unsigned int x, unsigned int y) -> void {
                auto primaryRay = SpaceConversion::pixelToPrimaryRay(x, y, maxWidth, maxHeight, 50, eyeTranslationMatrix);
                auto primaryRayCollision = findNearestRayCollision(primaryRay);

                if (primaryRayCollision.hitObject == std::nullopt) {
                    generateSkyPixel(r, g, b, y, maxWidth);
                    return;
                }

                auto currentRayCollision = primaryRayCollision;
                bool doneColoringReflections = false;
                for (unsigned int i = 0; i < MAXIMUM_REFLECTION_RECURSION; ++i) {
                    auto secondaryRay = lightTransport.calculatePixelColor(r, g, b, currentRayCollision, world);
                    if (secondaryRay == std::nullopt) {
                        doneColoringReflections = true;
                        break;
                    }

                    currentRayCollision = findNearestRayCollision(secondaryRay->ray);
                    auto noObjectFound = currentRayCollision.hitObject == std::nullopt;
                    if (noObjectFound) {
                        break;
                    }
                }

                if (!doneColoringReflections) {
                    generateSkyPixel(r, g, b, y, maxWidth);
                    r *= 0.8;
                    g *= 0.8;
                    b *= 0.8;
                }
            }
    );
}

RayCollision RayTracer::findNearestRayCollision(const Ray& ray) {
    float nearestGeometryIntersectionScalar = -1.0f;
    const std::shared_ptr<Geometry>* nearestGeometry = nullptr;
    for (const auto& geo : world.getGeometry()) {
        const float t = geo->getIntersectionScalarForRay(ray);
        if (t > nearestGeometryIntersectionScalar) {
            nearestGeometry = &geo;
            nearestGeometryIntersectionScalar = t;
        }
    }

    if (nearestGeometryIntersectionScalar < 1e-6) {
        return RayCollision(ray, ray.pointWithScalar(nearestGeometryIntersectionScalar));
    }

    return RayCollision(ray, ray.pointWithScalar(nearestGeometryIntersectionScalar), *nearestGeometry);
}

void
RayTracer::generateSkyPixel(GLubyte& r, GLubyte& g, GLubyte& b, const unsigned int& y, const unsigned int& maxHeight) {
    const float blendAmount = (float(y) / float(maxHeight));
    auto skyColor = lerp(SKY_LIGHT_COLOR, SKY_DARK_COLOR, blendAmount);
    r = skyColor.r * 255;
    g = skyColor.g * 255;
    b = skyColor.b * 255;
}
