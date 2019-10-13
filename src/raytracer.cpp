//
// raytracer.cpp
// Author: Samuel Vargas
// Date: 08/25/2019
//

#include "raytracer.h"
#include "lerp.h"
#include "spaceconversion.h"
#include <cassert>

static constexpr auto SKY_LIGHT_COLOR = linalg::vec<float,3>{0.8f, 0.8f, 0.8f};
static constexpr auto SKY_DARK_COLOR = linalg::vec<float,3>{0, 0.19607f, 0.298039f};
static unsigned int MAXIMUM_REFLECTION_RECURSION = 5;

RayTracer::RayTracer(
        RGBImageThreaded& rgbImage,
        const World& world, 
        const LightTransport& lightTransport) :
            rgbImage(rgbImage),
            world(world),
            lightTransport(lightTransport),
            translation(linalg::identity) {
}

RayTracer::RayTracer(
        RGBImageThreaded& rgbImage,
        const World& world,
        const LightTransport& lightTransport,
        const linalg::mat<float, 4,4>& translation) :
        rgbImage(rgbImage),
        world(world),
        lightTransport(lightTransport),
        translation(translation) {
}

void RayTracer::generateImage() {
    const auto maxWidth = rgbImage.getXRes();
    const auto maxHeight = rgbImage.getYRes();

    rgbImage.forEachPixelInParallel(
            [&](GLubyte& r, GLubyte& g, GLubyte& b, unsigned int x, unsigned int y) -> void {
                // TODO: Do NOT ignore the `translation` argument
                auto primaryRay = SpaceConversion::pixelToPrimaryRay(x, y, maxWidth, maxHeight, 50);
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
                    r = static_cast<GLubyte>(r * 0.8);
                    g = static_cast<GLubyte>(g * 0.8);
                    b = static_cast<GLubyte>(b * 0.8);
                }
            }
    );
}

RayCollision RayTracer::findNearestRayCollision(const Ray& ray) {
    float nearestGeometryIntersectionScalar = -1.0f;
    std::shared_ptr<Geometry> nearestGeometry;
    for (const auto& geo : world.getGeometry()) {
        const float t = geo->getIntersectionScalarForRay(ray);
        if (t > nearestGeometryIntersectionScalar) {
            nearestGeometry = std::shared_ptr<Geometry>(geo);
            nearestGeometryIntersectionScalar = t;
        }
    }

    if (nearestGeometryIntersectionScalar < 1e-6) {
        return RayCollision(ray, ray.pointWithScalar(nearestGeometryIntersectionScalar));
    }

    assert(nearestGeometry != nullptr);
    return RayCollision(ray, ray.pointWithScalar(nearestGeometryIntersectionScalar), nearestGeometry);
}

void
RayTracer::generateSkyPixel(GLubyte& r, GLubyte& g, GLubyte& b, const unsigned int& y, const unsigned int& maxHeight) {
    const float blendAmount = (float(y) / float(maxHeight));
    auto skyColor = lerp(SKY_LIGHT_COLOR, SKY_DARK_COLOR, blendAmount);
    r = static_cast<GLubyte>(skyColor.x * 255.0f);
    g = static_cast<GLubyte>(skyColor.y * 255.0f);
    b = static_cast<GLubyte>(skyColor.z * 255.0f);
}

